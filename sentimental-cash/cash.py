from cs50 import get_float


def main():
    # Taking input
    owed = getOwedAmount()
    # Coin counter
    coin = 0
    # List of funds available, in descending order (to be greedy)
    fund = [0.25, 0.10, 0.05, 0.01]
    # looping through the funds
    for amount in range(len(fund)):
        # while owed is greater than or equal to any of the amounts in the fund list
        while owed >= fund[amount]:
            # subtract that fund amount from owed and increase coin count
            owed = round(owed - fund[amount], 2)
            coin += 1
    # print coin count
    print(coin)


# get owed amount
def getOwedAmount():
    while True:
        changeOwed = get_float("Change owed: ")
        if changeOwed > 0:
            return changeOwed


main()