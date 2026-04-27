-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. Search for the crime scene report to get the initial details.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- 2. The report mentions three witnesses. Check the interviews table for their statements.
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;

-- 3. Ruth mentions the thief drove away from the bakery within 10 minutes of the theft.
-- Check the bakery_security_logs for license plates.
SELECT name
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = 'exit';

-- 4. Eugene mentions seeing the thief at an ATM on Leggett Street earlier that morning withdrawing money.
SELECT name
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- 5. Raymond mentions the thief called someone for less than a minute as they left the bakery.
-- They planned to take the earliest flight out of Fiftyville tomorrow (July 29).
SELECT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE month = 7 AND day = 28
AND duration < 60;

-- 6. Find the earliest flight on July 29th leaving Fiftyville and its destination.
SELECT airports.city, flights.id
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
)
AND flights.year = 2023 AND flights.month = 7 AND flights.day = 29
ORDER BY hour, minute
LIMIT 1;

-- 7. Combine the evidence: The thief must be in the bakery logs, the ATM list, the phone callers list,
-- and on that specific flight.
SELECT name
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = (
    SELECT id FROM flights
    WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
    AND year = 2023 AND month = 7 AND day = 29
    ORDER BY hour, minute LIMIT 1
)
AND name IN (
    SELECT name FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
)
AND name IN (
    SELECT name FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
)
AND name IN (
    SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE month = 7 AND day = 28 AND duration < 60
);

-- 8. Find the Accomplice: Look for who the thief (Bruce) called during that < 60s window.
SELECT name
FROM people
WHERE phone_number = (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
    AND month = 7 AND day = 28 AND duration < 60
);
