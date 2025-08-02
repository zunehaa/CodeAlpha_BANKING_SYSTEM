# CodeAlpha_BANKING_SYSTEM
This is a console-based Banking System developed in C++ as part of my internship with CodeAlpha. It simulates basic banking operations such as account creation, deposits, withdrawals, and balance inquiry—offering users an interactive way to manage their accounts within a terminal environment.
## Features:
  - "👤 Add New Customers with personal information"
  - "🏦 Open Savings or Current Accounts with initial deposit"
  - "💵 Deposit Money to any account with optional description"
  - "💸 Withdraw Money with real-time balance check"
  - "🔁 Transfer Money between accounts (intra-bank)"
  - "🧾 View Transaction History with timestamps and transaction IDs"
  - "📊 View Customer Info and All Linked Accounts"
  - "📜 List All Registered Customers"
  - "🧠 Interactive Console Menu with Clear Instructions"
  - "📂 Transactions stored in memory using C++ vectors and objects"

## Tech Stack:
  language: "C++"
 ## Tools: 
    - "Standard Template Library (STL)"
    - "OOP (Classes, Objects, Encapsulation)"
    - "File handling optional (currently in-memory)"
  dependencies: "None (Standard C++ Libraries Only)"
  platform: "Console / Terminal"

## How to use: 
  1. Clone or download the repository  
  2. Open the `.cpp` file in any C++-supported IDE (e.g., Code::Blocks, Dev-C++, Visual Studio)  
  3. Compile and run the code  
  4. Use the interactive menu to explore banking features

## Project Structure:
  - Transaction class: Handles transaction details (ID, type, amount, date, description)
  - Account class: Manages balance, deposit, withdraw, transfer, and transaction logs
  - Customer class: Stores personal data and manages multiple accounts
  - Bank class: Maintains list of all customers and allows account/customer lookup
  - Main function: Drives user interaction through a menu loop

## Learning Outcomes:
  - "Understanding Object-Oriented Programming in C++"
  - "Implementing real-world logic like transfers and balance updates"
  - "Working with `vectors`, `ctime`, `iomanip`, and string formatting"
  - "Designing clean class structures for modularity and scalability"

## Limitations:
  - "No persistent storage (all data lost on exit)"
  - "No authentication or password protection"
  - "Randomized account/customer/transaction IDs (not guaranteed unique)"
  - "Basic input validation only"

## Disclaimer: 
  This is a beginner-level project made for learning and demonstration purposes only. 
  It does not implement secure authentication, encryption, or real banking protocols.
