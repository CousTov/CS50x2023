import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks --- TODO"""
    # variables to store data
    updatedPrice = {}
    total_val = {}
    grandTotal = 0
    # user id for identification and extration of data from database
    userID = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", userID)
    name = username[0]["username"]
    userCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)
    cash = userCash[0]["cash"]
    purchases = db.execute(
        "SELECT stock_symbol, SUM(total_bought_stock) AS n FROM purchase_data WHERE username = ? GROUP BY stock_symbol", name)
    # calculating extracted data [the usd function is just for formatting]
    for purchase in purchases:
        currentPrice = lookup(purchase["stock_symbol"])
        updatedPrice[currentPrice["symbol"]] = usd(currentPrice["price"])
        val = float(currentPrice["price"]) * float(purchase["n"])
        grandTotal += float(cash) + float(val)
        total_val[currentPrice["symbol"]] = usd(val)
    cash = usd(cash)
    grandTotal = usd(grandTotal)

    soldPrices = {}
    total_sold_val = {}
    sells = db.execute("SELECT stock_symbol, total_sold_stock AS n FROM sell_data WHERE username = ? GROUP BY stock_symbol", name)
    for sell in sells:
        soldPrice = lookup(sell["stock_symbol"])
        soldPrices[soldPrice["symbol"]] = usd(soldPrice["price"])
        sellVal = float(soldPrice["price"]) * float(sell["n"])
        total_sold_val[soldPrice["symbol"]] = usd(sellVal)

    # returning to dashboard aka index.html
    return render_template("index.html", purchases=purchases, updated_price=updatedPrice, cash=cash, total_val=total_val, grand_total=grandTotal, sells=sells, soldPrices=soldPrices, total_sold_val=total_sold_val)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock -- TODO"""
    if request.method == "GET":
        # Display a form to buy
        return render_template("buy.html")

    else:
        # Purchase the stock so long as the user can afford it (cash column in users table from database)
        # (Use the session user id to select cash of user from users database table)
        symbol = request.form.get("symbol")
        lookedUp = lookup(symbol)
        # error handling
        if lookedUp == None:
            return apology("Company Not Found", 400)

        # no error:
        # get stock price,
        stockPrice = lookedUp["price"]
        # user id from session,
        userID = session["user_id"]
        # current cash user has,
        currentCash = db.execute("SELECT cash FROM users WHERE id = ?", userID)
        buyingUser = db.execute("SELECT username FROM users WHERE id = ?", userID)
        username = buyingUser[0]["username"]
        userCash = currentCash[0]["cash"]
        # and stocks (stock price x number of shares user wants to buy)
        userStockAmount = request.form.get("shares")
        # check if the stock amount is valid
        try:
            int(userStockAmount)
        except ValueError:
            return apology("Invalid Stock Amount", 400)
        userStockAmount = int(userStockAmount)
        if userStockAmount <= 0:
            return apology("Invalid Stock Amount", 400)
        stocksPrice = stockPrice * userStockAmount
        # Check if user has enough cash
        if userCash >= stocksPrice:
            # user's new cash after purchase
            newCash = userCash - stocksPrice
            # updating database with the subtracted/new cash value
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userID)
            # getting additional purchase info
            boughtDateTime = db.execute("SELECT DATETIME('now') as date_and_time")
            dateAndTime = boughtDateTime[0]["date_and_time"]
            # storing purchase info
            db.execute("INSERT INTO purchase_data(username, stock_symbol, stock_price, total_bought_stock, date_and_time) VALUES(?, ?, ?, ?, ?)",
                       username, symbol, stockPrice, userStockAmount, dateAndTime)
            return redirect("/")
        else:
            return apology("Insufficient Cash", 400)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Display html table with a history of all transaction's, listing one row for every buy and every sell
    # get all data from purchase_data and sold_data (table to be made in /sell) appriopirately
    # return render_template("history.html") (to be made)
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote. -- DONE"""
    # if get  request is made, display form to request a stock quote
    if request.method == "GET":
        # display form
        return render_template("quote.html")
    # post method does the following
    else:
        # lookup the stock symbol and display results
        symbol = request.form.get("symbol")
        lookedUp = lookup(symbol)
        if lookedUp != None:
            latestPrice = usd(lookedUp["price"])
            name = lookedUp["name"]
            return render_template("quoted.html", symbol=symbol, latestPrice=latestPrice, name=name)
        return apology("Company Not Found", 400)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user -- DONE"""

    # get request returns register form
    if request.method == "GET":
        return render_template("register.html")
    # post request does the following
    else:
        # check errors
        # username
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # password
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # if no errors
        # store usename and passowrd user entered in the form in variables
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        confirmPass = request.form.get("confirmation")

        # check for passowrd confirmation
        if check_password_hash(password, confirmPass) == False:
            return apology("Password Confirmation Failed", 400)

        # storing username from database
        existUser = db.execute("SELECT username FROM users WHERE username = ?", username)
        # check if username exists
        if existUser:
            return apology("username is already taken", 400)

        # if user doesn't exist, add the user adn password hash into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)
        # Taking the newly inserted user's id from database
        id = db.execute("SELECT id FROM users WHERE username = ?", request.form.get("username"))
        # setting session token for that user
        session["user_id"] = id
        return redirect("/", 200)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock - TODO"""
    if request.method == "GET":
        # Display from to sell a stock
        username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
        purchases = db.execute(
            "SELECT stock_symbol FROM purchase_data WHERE username = ? GROUP BY stock_symbol", username[0]["username"])
        forOptions = []

        for purchase in purchases:
            forOptions.append(purchase["stock_symbol"])

        return render_template("sell.html", options=forOptions)
    else:
        # error handling
        symbol = request.form.get("symbol")
        shareAmount = request.form.get("shares")

        if not symbol:
            return apology("Must provide stock symbol", 400)

        elif not shareAmount:
            return apology("Must provide number of shares", 400)

        userID = session["user_id"]
        user = db.execute("SELECT username, cash FROM users WHERE id = ?", userID)
        username = user[0]["username"]
        userCash = user[0]["cash"]
        purchases = db.execute(
            "SELECT stock_symbol, SUM(total_bought_stock) AS n FROM purchase_data WHERE username = ? GROUP BY stock_symbol", username)
        owned = []
        ownedShares = {}

        for purchase in purchases:
            owned.append(purchase["stock_symbol"])
            ownedShares[purchase["stock_symbol"]] = purchase["n"]
        if symbol not in owned:
            return apology("You do not own any share of this stock", 400)
        try:
            int(shareAmount)
        except ValueError:
            return apology("Invalid Stock Amount", 400)
        shareAmount = int(shareAmount)
        if ownedShares[symbol] < shareAmount:
            return apology("Invalid number of stock to sell", 400)

        lookedUp = lookup(symbol)
        currentPrice = lookedUp["price"]
        soldDateAndTime = db.execute("SELECT DATETIME('now') as date_and_time")
        dateAndTime = soldDateAndTime[0]["date_and_time"]
        soldProfit = float(currentPrice) * float(shareAmount)
        newCash = soldProfit + float(userCash)

        db.execute("INSERT INTO sell_data(username, stock_symbol, stock_price, total_sold_stock, date_and_time) VALUES(?, ?, ?, ?, ?)",
                   username, symbol, currentPrice, shareAmount, dateAndTime)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userID)
        return redirect("/")
        # return apology("TODO")


@app.route("/personal-touch", methods=["GET", "POST"])
@login_required
def personalTouch():
    # allow users to delete their account and it's data.
    # if get, render deletion form
    # if post, get deletion request with passowrd confirmation
    # make sure user exists and password confirmation is valid, then delete all the user's data from database.
    return apology("TODO")