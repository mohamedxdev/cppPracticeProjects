
# 🏦 Banking System  C++



A secure console-based banking application with client management, user permissions, and transaction processing.

## ✨ Features

### 👥 Client Management
- ✅ Add/Delete/Update clients
- 🔍 Find clients by account number
- 📋 List all clients with details

### 👤 User Management
- 🛡️ Role-based permissions system
- 👑 Admin privileges
- 🔒 Secure login system

### 💰 Transactions
- 💵 Deposit/Withdraw funds
- 📊 View total balances
- ⚠️ Withdrawal validation

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++ recommended)
- C++17 or later


## 🖥️ Usage

```text
===========================================
          Main Menu Screen
===========================================
  [1] Show Client List
  [2] Add New Client
  [3] Delete Client
  [4] Update Client
  [5] Find Client
  [6] Transactions
  [7] Manage Users
  [8] Logout
===========================================
```

## 📂 File Structure
```bash
.
├── Clients.txt    # Client database
├── Users.txt      # User credentials
└── main.cpp       # Source code
```

## 🔐 Default Admin
To set up initially:
1. Create `Users.txt` with:
```text
Admin#//#your_password#//#-1
```

## 📊 Data Structure
Client records use `#//#` delimiter:
```text
ACC123#//#1234#//#John Doe#//#555-1234#//#1000.00
```

