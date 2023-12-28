-- Keep a log of any SQL queries you execute as you solve the mystery.

-- As per the walkthrough, I read the description from crime scene report using:
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

 -- The description had some details -- Theft time: 10:15AM at the Humphery Street Bakery -- 3 Wittness Interview transcript mentioned the bakery
 -- Littering took place at 16:36PM WITH NO WITTNESES -- This event is of no use.

 -- CHECKING WITTNESS NAMES AND TRANSCRIPT
 SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28;

 -- WITTNESS ARE Eugene, Raymond And Ruth
 -- Clue1: Within 10 min of the theft, theif left the parking lot on his car,
 -- Clue2: Earlier in the morining, before Eugene interned the bakery, he saw thief withrawing some money from the Leggett Street atm,
 -- Clue3 : Raymond wittnessed teh thief calling someone and having a < 1 min call where the thief said to the person on the phone to book the earliest flight out of fiftyville tomorrow

 -- CHECKING WHO LEFT THE PARKING LOT AFTER THE THEFT
 SELECT * FROM bakery_security_logs WHERE hour = 10 AND minute < 25 AND minute > 15 AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit';
 -- 9 LICENSE PLATES
 -- PEOPLE WHO LEFT WITHIN 10 MIN OF ROBBERY
 SELECT NAME FROM PEOPLE WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE hour = 10 AND minute < 25 AND minute > 15 AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit');
 /*
    Vannessa
    Barry
    Iman
    Sofia
    Luca
    Diana
    Kelsey
    Bruce
 */

 -- CHECKING ATM transactions
 SELECT * FROM atm_transactions WHERE transaction_type = 'withdraw' AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';
 -- 8 withdraws

 -- CHECKING CALL LOGS
 SELECT * FROM phone_calls WHERE duration < 60 AND year = 2021 AND month = 7 AND day = 28;
 -- 9 CALLERS

 -- CHECKING Early Morning flight DATA
 SELECT * FROM flights WHERE hour < 12 AND Month = 7 AND day = 29;
 -- TWO FLIGHTS: 4 and 1
 SELECT * FROM airports WHERE id IN (4, 1);
 -- O'Hare International Airport, Chicago AND LaGuardia Airpirt, NYC

 -- FILTERING PASSENGERS WITH PHONE NUMBER, LISENSE PLATE, AND NAME OF THOSE WHO LEFT
 SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE hour < 12 AND Month = 7 AND day = 29)) AND phone_number IN (SELECT caller FROM phone_calls WHERE duration < 60 AND year = 2021 AND month = 7 AND day = 28) AND name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE hour = 10 AND minute > 15 AND minute < 25 AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit'));
 -- SOFIA
 -- KELSYE
 -- BRUCE

-- GETTING THEIR FLIGHT IDs
SELECT flight_id FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE hour < 12 AND Month = 7 AND day = 29)) AND phone_number IN (SELECT caller FROM phone_calls WHERE duration < 60 AND year = 2021 AND month = 7 AND day = 28) AND name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE hour = 10 AND minute > 15 AND minute < 25 AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit')));
-- FLIGHT ID 36's DESTINATION AIRPORT ID IS 4
-- GETTING WHERE THEY ARE HEADED WITH DESTINATION AIRPORT ID
SELECT * FROM airports WHERE id = 4;
-- HEADED TO NY

-- FILTERING FURTHER WITH THE ATM TRANSACTION RECORDS
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE hour < 12 AND Month = 7 AND day = 29)) AND phone_number IN (SELECT caller FROM phone_calls WHERE duration < 60 AND year = 2021 AND month = 7 AND day = 28) AND name IN (SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE hour = 10 AND minute > 15 AND minute < 25 AND year = 2021 AND month = 7 AND day = 28 AND activity = 'exit') AND name IN (SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE transaction_type = 'withdraw' AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'))));

-- THIEF IS BRUCE
-- HEADED TO NY

SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = 'Bruce') AND duration < 60 AND year = 2021 AND month = 7 AND day = 28);
-- ACOMPLICE IS Robin