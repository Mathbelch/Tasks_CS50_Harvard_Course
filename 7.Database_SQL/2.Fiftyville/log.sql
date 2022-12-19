-- Keep a log of any SQL queries you execute as you solve the mystery.

-- What do we know:
-- Date: July 28
-- Street: Chamberlin Street

-- (1) First let's search for any crime scene report on the specified date and street.
SELECT description, year FROM crime_scene_reports WHERE (month = 7) AND (day = 28) AND (street LIKE 'Chamberlin Street');
-- insights: it happens at 10:15am on 28 July, 2020
-- 3 witnesses interviewed (2) - each of their interview transcripts mentions the courthouse.

-- (2)  Let's then look for those 3 people interviews:
SELECT name, transcript FROM interviews WHERE (transcript LIKE '%courthouse%') AND (year = 2020) AND (month >= 7);
-- (A) Ruth: after 10 minutes she saw the thief getting a car on the parking lot;
-- (B) Eugene: recognized the thief from the ATM on Fifer Street withdrawing some money;
-- (C) Raymond: saw the thief calling someone for less than a minute, saying they'd take the earliest flight to leave the city. The accomplice would purchase the flight Tickets;


-- Let's get the witness informations: PHONE ; PASSPORT ; LICENSE PLATE
SELECT * FROM people WHERE name = 'Eugene' OR name = 'Ruth' OR name = 'Raymond';
-- EUGENE: (666) 555-5774 ; 9584465633 ; 47592FJ
-- RUTH: (772) 555-5770   ; -  ; HZB4129
-- RAYMOND: (125) 555-8030   ;   - ; Y18DLY3

-- (A) Let's look for the courthouse security cameras DB on that date. Considering the crime happened at around 10:15, the person would had left at around 10:25 according to Ruth. So this query looks for people leaving after 10:15.
SELECT activity, license_plate, minute FROM courthouse_security_logs WHERE (year = 2020) AND (month = 7) AND (day = 28) AND (hour = 10) AND (minute >= 15);
-- This query allows to get people's name, plate and minute that left the place.
SELECT people.name, people.license_plate, courthouse_security_logs.minute FROM people, courthouse_security_logs WHERE ((people.license_plate LIKE courthouse_security_logs.license_plate) AND (courthouse_security_logs.year = 2020) AND (courthouse_security_logs.month = 7) AND (courthouse_security_logs.day = 28) AND (courthouse_security_logs.hour = 10) AND (courthouse_security_logs.minute >= 15) AND (courthouse_security_logs.activity LIKE 'exit')) ORDER BY name;

-- SUSPECT LIST: Amber, Danielle, Elizabeth, Ernest, Evelyn, Madison, Patrick, Roger, Russel


-- (B) Let's look the ATM records from fifty street:
SELECT * FROM atm_transactions WHERE atm_location LIKE 'Fifer Street' AND transaction_type LIKE 'withdraw' AND month = 7 AND day = 28 AND year = 2020;

SELECT name, atm_transactions.amount FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE (atm_transactions.atm_location LIKE 'Fifer Street' AND atm_transactions.transaction_type LIKE 'withdraw' AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.year = 2020) ORDER BY name;

-- SUSPECT LIST: Bobby, Danielle, Elizabeth, Ernest, Madison, Roy, Russell, Victoria

-- Repeated names on A and B: Danielle, Elizabeth, Ernest, Madison, Russel.

-- (C) Let's look for the people who made or receive a phone call for less than 60 seconds on that day.
SELECT people.name, people.phone_number, phone_calls.caller, phone_calls.receiver, phone_calls.duration FROM people, phone_calls WHERE ((people.phone_number = phone_calls.caller) AND (phone_calls.day = 28) AND (phone_calls.month = 7) AND (phone_calls.year = 2020) AND (phone_calls.duration <= 60)) ORDER BY duration ASC;
-- Callers: Evelyn, Kimberly, Madison, Ernest, Russell, Evelyn, Roger, Victoria, Bobby, Kathryn
---------------------------------------------------------
SELECT people.name, people.phone_number, phone_calls.caller, phone_calls.receiver, phone_calls.duration FROM people, phone_calls WHERE ((people.phone_number = phone_calls.receiver) AND (phone_calls.day = 28) AND (phone_calls.month = 7) AND (phone_calls.year = 2020) AND (phone_calls.duration <= 60)) ORDER BY duration ASC;
-- Receivers: Larry, Jacqueline, James, Berthold, Philip, Melissa, Jack, Anna, Doris, Danielle

-- Repeated names on A, B, and C: Danielle, Ernest, Madisson, Russell

-- (C) Let's look if any of the people on the suspect list were on the first flight to leave the city the next day:
SELECT flights.id, airports.city, flights.day, flights.hour, flights.minute FROM flights, airports WHERE ((year = 2020) AND (month = 7) AND (day > 28) AND (flights.origin_airport_id IN (SELECT airports.id FROM airports WHERE city LIKE 'Fiftyville')) AND (flights.destination_airport_id = airports.id)) ORDER BY flights.day, flights.hour;
-- Cheking list of passengers on the first flight, to London (id = 36):
SELECT people.name, passengers.seat FROM people, passengers WHERE (people.passport_number = passengers.passport_number) AND (passengers.flight_id = 36) ORDER BY name;
-- Repeated names: Danielle, Ernest, Madison.

-- Let's check the flight movimentation of these 3 people:
SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name LIKE 'Danielle'));
-- Danielle went back to fiftyville on July 30.
SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name LIKE 'Ernest'));
-- Ernest's only flight is to London.
SELECT * FROM flights WHERE id IN (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name LIKE 'Madison'));
-- Madison's only flight is to London.

-- MAIN SUSPECTS: Ernest and Madison.
-- Ernest: Lefts the crime scene at 10:18 and got $50 on the ATM.
-- Madison: Lefts the crime scene at 10:35 and got $60 on the ATM.

-- Considering the time, the thief is probably Ernest, who left to London with the help of Berthold.

