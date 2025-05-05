# Overview
This project is a prototype implementation of a student meal payment system using Arduino and an RFID card reader (MFRC522). It simulates how a student can "tap" their RFID card to access meals in a university canteen. The system identifies students using their RFID UID, checks their meal balance, deducts payment if sufficient, and logs the transaction to the Serial Monitor.

This is a local, offline prototype intended to demonstrate the core logic before full backend integration (e.g., Django or other server-side applications).

# Features
Reads RFID cards using MFRC522 module

Matches scanned UID to hardcoded student records

Simulates real-time transaction timestamp using millis()

Verifies student balance and deducts 1000 units per meal

Logs transaction status and new balance to Serial Monitor

Identifies unknown cards with a user-friendly error message

# Project Status
 Core logic implemented
 Not connected to a backend yet
 No persistent storage (e.g., EEPROM or SD card)
 Future improvements: backend integration, real-time clock (RTC), LCD display, and database connectivity

# Future Enhancements
Integrate with Django backend for persistent logs and balance updates

Use real-time clock (RTC) for accurate time stamping

Add LCD or OLED screen for display without a computer

Secure storage of UIDs and balances (EEPROM or SD)

