CALORIE TRACKER PRO
Video Demo: https://www.youtube.com/watch?v=OrSCjtDpsm0
Name: Salah-Eddine Kanoun
City / Country: Morocco
GitHub Username: kanSal1229
Project Overview

Calorie Tracker Pro is a dynamic web-based application designed to help individuals monitor their daily health and nutrition. Developed as a final project for CS50’s Introduction to Computer Science, this tool allows users to register personal accounts, log in securely, and record their food intake throughout the day. The application then calculates the total caloric value for the current day and displays it against a recommended daily intake of 2000 calories.

Distinctiveness and Complexity
This project stands out by moving beyond a simple "to-do list" application. It manages a complex relationship between user authentication and personalized data retrieval.

Security: Instead of storing plain-text passwords, the application utilizes the werkzeug.security library to hash and check passwords, ensuring that user data remains protected even if the database is accessed.

Relational Database: I designed a multi-table SQLite database where the entries table is linked to the users table via a foreign key (user_id). This ensures that when Jovany or any other user logs in, they only see their specific data.

Real-time Logic: The application uses SQL's CURRENT_DATE function to automatically filter results, meaning the user's dashboard resets every 24 hours without manual intervention.

File Structure and Functionality
app.py
This is the controller of the application. It contains the Flask routes that handle the logic for:

User Registration: Validating unique usernames and storing hashed credentials.

Session Management: Using flask_session to keep users logged in across different pages.

Calorie Calculation: Running SQL SUM queries to aggregate calories for the current day.

tracker.db
The SQLite database file. It was initialized using the sqlite3 command-line tool and contains the following schema:

users: Stores id, username, and hash.

entries: Stores id, user_id, food_name, calories, and date.

templates/
layout.html: The base template featuring a Bootstrap navigation bar, allowing users to toggle between "Accueil" (Home), "Ajouter un aliment" (Add Food), and "Déconnexion" (Logout).

index.html: The main dashboard as seen in the project screenshots. It uses Jinja2 loops to display the user's food log in a clean, professional table.

add.html: The interface where users input their food items and calorie values.

static/styles.css
Contains custom styling to enhance the default Bootstrap layout, specifically focusing on the typography and the "Today's Summary" header for better user experience.

Design Choices
During development, I chose to implement a simple, minimalist UI to ensure that users—particularly those in Morocco using mobile devices—could quickly log their meals without heavy page load times. I also decided to implement a manual "Add Food" system rather than an automated search to keep the application lightweight and functional without relying on expensive third-party APIs for this stage of the project.

How to Run
Navigate to the final_project directory.

Initialize the database tables if they do not exist using the commands in the terminal.

Execute flask run.

Visit the local server link and register an account to begin tracking.
