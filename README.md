# 🏦 Bank Management System (BMS) in C

A terminal-based Bank Management System (BMS) built in C, designed to simulate basic banking operations for clients and administrators. This project demonstrates the implementation of account creation, transactions, access control, and data persistence using file I/O in the C language.

---

## 📌 Features

### 👨‍💼 Admin Panel
- Secure login using credentials stored in a private config header
- Create new bank accounts with auto-generated IDs and passwords
- Open and manage existing accounts
  - Deposit or withdraw funds
  - Change account status (Active, Restricted, Closed)
  - Transfer funds between accounts

### 👤 Client Panel
- Login using account ID and password
- View and manage personal account
  - Transfer money to other users
  - Deposit or withdraw cash
  - Change password securely

### 📁 Data Storage
- User data is stored in a flat file (`accounts.txt`) in a structured format
- All operations (create, update, transaction) update the file persistently
- File format: `account_id|full_name|address|age|national_id|password|balance|status`

---

## 🛠 Technologies Used

- Language: C
- Compiler: GCC
- I/O: Standard C file handling (`fopen`, `fscanf`, `fprintf`)
- Terminal UI: Light screen clearing and formatting for better UX

---
## Compile the Project
- gcc src/main.c src/account.c src/admin.c src/client.c -Iinclude -o bank_system.exe
## Run the Program
- ./bank_system.exe
