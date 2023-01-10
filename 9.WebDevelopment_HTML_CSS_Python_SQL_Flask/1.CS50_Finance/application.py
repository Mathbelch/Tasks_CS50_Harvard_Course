# api_key token: export API_KEY=pk_c6532692b8fc4de9b546e99d61f5cd18

import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure Flask application:
app = Flask(__name__)

# Ensure templates are auto-reloaded:
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached:
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom jinja filter in order to make it easier to formate values as american dollars:
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies, which is the dafult in Flask):
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database:
db = SQL("sqlite:///finance.db")

# Make sure API key is set:
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

############# ROUTES #############

@app.route("/")
@login_required # User must be logged in to see this page!
def index():
    """Show portfolio of stocks user owns"""
    stocks = db.execute("SELECT Symbol, SUM(shares) FROM transactions WHERE userID == ? GROUP BY Symbol HAVING SUM(shares) > 0", session["user_id"])

    # Cheking if user has any stock:
    if not stocks:
        cash = round(float(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']), 2)
        return render_template("index.html", cash=usd(cash), totalAmount=usd(cash))

    else:
        # Getting informations about each of user's stocks and pdating user's informations::
        totalValueStocks = 0
        for stock in stocks:
            stock['name'] = lookup(stock['Symbol'])['name']
            stock['price'] = usd(round(lookup(stock['Symbol'])['price'], 2))
            stock['total'] = round(lookup(stock['Symbol'])['price'] * stock['SUM(shares)'], 2)
            stock['amount'] = stock['SUM(shares)']
            totalValueStocks += stock['total']
            stock['total'] = usd(stock['total'])

        cash = round(float(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']), 2)
        totalAmount = totalValueStocks + cash
        return render_template("index.html", stocks=stocks, cash=usd(cash), totalAmount=usd(totalAmount))


@app.route("/buy", methods=["GET", "POST"])
@login_required # User must be logged in to see this page!
def buy():
    """Buy shares of stock"""

    # User reached route via GET (as by clicking a link or via redirect), we must display search form to the user insert the quote symbol and the amount of shares:
    if request.method == "GET":
        return render_template("buy.html")

    # User reached route via POST (as by submitting the form), check the form values and, if it's all good, insert data in finance.db:
    else:

        # Ensure symobol was submitted:
        if not request.form.get("symbol"):
            return apology("You must provide a symbol", 400)

        # Ensure symbol exists:
        elif lookup(request.form.get("symbol")) == None:
            return apology("This stock does not exist", 400)

        # Ensure amount of shares was submitted:
        elif not request.form.get("shares"):
            return apology("You must provide the amount of shares", 400)

        # Ensure amount of shares is an int higher than 0:
        shares = request.form.get("shares")
        if (not shares.isnumeric()) or (int(shares) <= 0):
            return apology("Shares must be an integer higher than 0", 400)

        # Ensure user has enough money to buy the amount of shares submited:
        results = lookup(request.form.get("symbol"))
        total = (results["price"]) * int(request.form.get("shares"))
        balance = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]

        if float(balance["cash"]) < total:
            return apology("You don't have enough money to buy this amount of shares", 400)

        # If it's all good we can save transaction's data on database and update user's cash value:
        else:
            db.execute("INSERT INTO transactions (symbol, name, shares, price, date, userID) VALUES (?, ?, ?, ?, ?, ?)", request.form.get("symbol"), results["name"], int(request.form.get("shares")), results["price"], datetime.today(), session["user_id"])
            db.execute("UPDATE users SET cash = ? WHERE id == ?", balance["cash"] - total, session["user_id"])
            flash('Bought')
            return redirect("/")

@app.route("/history")
@login_required # User must be logged in to see this page!
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT Symbol, shares, price, date FROM transactions WHERE userID == ? ORDER BY date DESC", session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id:
    session.clear()

    # User reached route via POST (as by submitting a form via POST):
    if request.method == "POST":

        # Ensure username was submitted:
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted:
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username:
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct:
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in:
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page:
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect):
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id:
    session.clear()

    # Redirect user to login form:
    return redirect("/login")


@app.route("/quote", methods=["GET", "POST"])
@login_required # User must be logged in to see this page!
def quote():
    """Get stock quote."""

    # User reached route via GET (as by clicking a link or via redirect), we must display search form to the user request a stock quote:
    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST (as by submitting the form), we must lookup the stock symbol by calling the lookup function, displaying the results:
    else:
        results = {}
        results = lookup(request.form.get("symbol"))
        if results == None:
            return apology("This stock does not exist", 400)
        else:
            return render_template("/quoted.html", results=results, price=usd(results["price"]))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id:
    session.clear()

    # User reached route via GET (as by clicking a link or via redirect), we must display registration form:
    if request.method == "GET":
        return render_template("register.html")

    # User reached route via POST (as by submitting the form), we must check the input, hash the password and then insert the new user into users table:
    else:
        # Ensure username was submitted:
        if not request.form.get("username"):
            return apology("You must provide a username", 400)

        # Ensure username is not already in finance.db:
        elif (db.execute("SELECT username FROM users WHERE username LIKE ?", request.form.get("username"))):
            return apology("This username already exists", 400)

        # Ensure password was submitted:
        elif not request.form.get("password"):
            return apology("You must provide a password", 400)

        # Ensure confirmation password was submitted:
        elif not request.form.get("confirmation"):
            return apology("You must provide a confirmation password", 400)

        # Ensure confirmation password matches passward:
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("Passwords must be the same", 400)

        # If it's all good, we save user data on finance.db:
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
            return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required # User must be logged in to see this page!
def sell():
    """Sell shares of stock"""

    # User reached route via GET (as by clicking a link or via redirect), we must display search form to the user insert the quote symbol and the amount of shares:
    if request.method == "GET":
        stocks = db.execute("SELECT Symbol, SUM(shares) FROM transactions WHERE userID == ? GROUP BY Symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", stocks=stocks)

    # User reached route via POST (as by submitting the form), check the form values and, if it's all good, insert data in finance.db:
    else:
        # Ensure symobol was submitted:
        if not request.form.get("symbol"):
            return apology("You must provide a symbol", 400)

        # Ensure symbol exists:
        elif lookup(request.form.get("symbol")) == None:
            return apology("This stock does not exist", 400)

        # Ensure amount of shares was submitted:
        elif not request.form.get("shares"):
            return apology("You must provide the amount of shares", 400)

        # Ensure amount of shares is an int higher than 0:
        shares = request.form.get("shares")
        if (not shares.isnumeric()) or (int(shares) <= 0):
            return apology("Shares must be an integer higher than 0", 400)

        # Ensure user has the amount of shares it wants to sell:
        stocks = db.execute("SELECT SUM(shares) FROM transactions WHERE userID == ? AND Symbol LIKE ?", session["user_id"], request.form.get("symbol"))[0]['SUM(shares)']
        print(stocks)
        if not stocks:
            return apology("You don't have shares from that company")

        elif int(stocks) < int(request.form.get("shares")):
            return apology("You don't have this amount of shares from that company")

        # If it's all good, we can update the database:
        else:
            results = lookup(request.form.get("symbol"))
            valueSell = int(results["price"]) * int(request.form.get("shares"))
            balance = db.execute("SELECT cash FROM users WHERE id == ?", session["user_id"])[0]
            db.execute("INSERT INTO transactions (symbol, name, shares, price, date, userID) VALUES (?, ?, ?, ?, ?, ?)", request.form.get("symbol"), results["name"], int(request.form.get("shares")) * -1, results["price"], datetime.today(), session["user_id"])
            db.execute("UPDATE users SET cash = ? WHERE id == ?", balance["cash"] + valueSell, session["user_id"])
            flash('Sold')
            return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
