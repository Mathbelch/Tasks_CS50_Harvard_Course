from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session

# Configure application:
app = Flask(__name__)
# Setting secret_key from flask:
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

# Ensure templates are auto-reloaded:
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database:
db = SQL("sqlite:///birthdays.db")

# Configure request forms:
@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        birthdays = []
        birthdays = db.execute("SELECT name FROM birthdays")

        # Cheking if name was submited:
        if not request.form.get("name"):
            flash("Please provide a name!")
            return redirect("/")

        # Cheking if there is no name equal the one submited:
        for birthday in birthdays:
            if request.form.get("name").capitalize() == birthday["name"]:
                flash("This name is already on database, please provide a second name!")
                return redirect("/")

        # Cheking if day was submited:
        if not request.form.get("day"):
            flash("Please provide the day of your birthday!")
            return redirect("/")

        # Cheking if month was submited:
        if not request.form.get("month"):
            flash("Please provide the month of your birthday!")
            return redirect("/")

        # If it's all good, we can add data on database:
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", request.form.get("name").capitalize(), int(request.form.get("month")), int(request.form.get("day")))
        flash("Added!")
        return redirect("/")

    # If user enter the page by URL or Link, it gets the route via GET:
    else:
        # Display the entries in the database on index.html:
        birthdays = []
        birthdays = db.execute("SELECT name, day, month FROM birthdays ORDER BY name ASC")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete", methods=["GET", "POST"])
def delete():
    if request.method == "POST":
        name = request.form.get("deleteName")
        db.execute("DELETE FROM birthdays WHERE name LIKE ?", name)
        flash("Deleted!")
        return redirect("/")