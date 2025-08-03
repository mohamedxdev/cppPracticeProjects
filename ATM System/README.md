
# ATM System 💻🏦  

**A C++ console application simulating core ATM functionalities with file-based data storage**  

## Features ✨  
- 🔐 Secure login with account number/PIN verification  
- 💸 **Withdrawal Options**:  
  - Quick cash (preset amounts)  
  - Custom amounts (multiples of 5)  
- 💰 Deposit funds  
- 📊 Balance inquiry  
- 🏦 Persistent account data (text file storage)  

## Technical Highlights ⚙️  
- **File I/O Operations**: Stores client data in `Clients.txt`  
- **Structured Data**: Uses `sClient` struct to manage account info  
- **Modular Design**: Separates concerns with dedicated functions for each operation  
- **Input Validation**: Ensures proper transaction amounts  

## Usage 🚀  
1. Compile and run the C++ program  
2. Login with credentials from `Clients.txt`  
3. Select transaction type from menu  

## Data Format 📝  
Accounts are stored with `#//#` delimiter:  
```
AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance
```  

> **Note**: Requires proper `Clients.txt` file with client records  

---  
*C++ Console Application*
