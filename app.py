import os
from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from werkzeug.security import check_password_hash, generate_password_hash

# Configure application
app = Flask(__name__)
app.secret_key = "make_this_a_secret_string"

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///tracker.db")

@app.route("/")
def index():
    """Show dashboard with total calories for today"""
    if "user_id" not in session:
        return redirect("/login")

    # Get today's entries for the logged-in user
    entries = db.execute(
        "SELECT food_name, calories FROM entries WHERE user_id = ? AND date = CURRENT_DATE",
        session["user_id"]
    )

    # Calculate total calories
    total_calories = sum(entry["calories"] for entry in entries)

    return render_template("index.html", entries=entries, total=total_calories)

@app.route("/add", methods=["GET", "POST"])
def add():
    """Add a new food entry"""
    if "user_id" not in session:
        return redirect("/login")

    if request.method == "POST":
        food = request.form.get("food")
        calories = request.form.get("calories")

        # Insert into database
        db.execute(
            "INSERT INTO entries (user_id, food_name, calories) VALUES (?, ?, ?)",
            session["user_id"], food, calories
        )
        return redirect("/")
    else:
        return render_template("add.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return "Invalid username or password" # You can replace this with an apology template

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("login.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # Hash the password
        hash_pass = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pass)
            return redirect("/login")
        except ValueError:
            return "Username already exists"
    else:
        return render_template("register.html")

@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")
