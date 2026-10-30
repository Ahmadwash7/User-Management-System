# 🏦 Bank Clients Management System

> A simple and interactive **C++ console application** for managing bank client records and system users, with login, role-based permissions, and persistent file storage.

This project was built to practice **problem solving, functions, structs, file handling, vectors, bitwise permissions, input validation, and clean code organization** using C++.

---

## 🚀 What Can You Do?

After logging in, the main menu gives you access to:

| Option | Feature            | Description                                           |
| :----: | ------------------ | ----------------------------------------------------- |
|  📋 1  | **Show Clients**   | Display all registered clients in a formatted table   |
|   ➕ 2  | **Add Client**     | Add one or multiple new clients                       |
|  🗑️ 3 | **Delete Client**  | Find and delete a client after confirmation           |
|  ✏️ 4  | **Update Client**  | Update a client's information                         |
|  🔎 5  | **Find Client**    | Search for a client using their account number        |
|  💵 6  | **Transactions**   | Deposit, withdraw, and view total balances            |
|  👥 7  | **Manage Users**   | List, add, delete, update, and find system users      |
|  🚪 8  | **Logout**         | Go back to the login screen                           |

Every option is protected by a **permission check**. If the logged-in user doesn't have access, an *Access Denied* screen is shown.

---

## 🔐 Login & Permissions

The program starts with a login screen:

```text
===========================================
              Login
===========================================
Enter UserName:
Enter Password:
```

Wrong credentials show `Invalid UserName/Password!` and ask again.

### Permission system

Each user has a single number (`Permissions`) built from **bit flags**:

| Permission        | Value |
| ----------------- | :---: |
| List Clients      |   1   |
| Add New Client    |   2   |
| Delete Client     |   4   |
| Update Client     |   8   |
| Find Client       |  16   |
| Transactions      |  32   |
| Manage Users      |  64   |
| **Full Access**   | **-1** |

Permissions are combined by adding the values (for example `1 + 16 = 17` means *List Clients* + *Find Client*), and checked with a bitwise AND:

```cpp
(User.Permissions & RequiredPermission) == RequiredPermission
```

A user with `-1` has access to everything.

### Default users (sample)

| Username | Password | Permissions | Meaning                                                |
| -------- | -------- | :---------: | ------------------------------------------------------ |
| Admin    | 1234     |     -1      | Full access                                            |
| User1    | 1111     |     31      | List, Add, Delete, Update, Find (no Transactions/Users) |
| User2    | 2222     |     17      | List + Find                                            |
| User3    | 3333     |      7      | List, Add, Delete                                      |

---

## 💵 Transactions Menu

Selecting **[6] Transactions** opens a dedicated submenu:

```text
===========================================
         Transactions Menu Screen
===========================================
     [1] Deposit.
     [2] Withdraw.
     [3] Total Balances.
     [4] Main Menu.
===========================================
```

* **Deposit** — enter an account number, then a positive amount to add to that client's balance (with confirmation before saving).
* **Withdraw** — enter an account number, then an amount to subtract, validated against the client's available balance (with confirmation before saving).
* **Total Balances** — lists every client's balance in a table and prints the grand total across all accounts.
* **Main Menu** — returns to the main menu.

---

## 👥 Manage Users Menu

Selecting **[7] Manage Users** (requires the *Manage Users* permission) opens:

```text
===========================================
        Manage Users Menu Screen
===========================================
     [1] List Users.
     [2] Add New User.
     [3] Delete User.
     [4] Update User.
     [5] Find User.
     [6] Main Menu.
===========================================
```

* **List Users** — shows all users with their passwords and permission values.
* **Add New User** — username (must be unique), password, then either full access or a yes/no question for each permission.
* **Delete User** — finds the user, asks for confirmation, then removes them.
* **Update User** — change a user's password and permissions.
* **Find User** — shows a user's details card.

---

## 💾 Data Persistence

The system uses two text files, so your data **doesn't disappear when the program closes**.

### `Clients.txt`

```text
AccountNumber#//#PinCode#//#Name#//#PhoneNumber#//#Balance#//#
```

```text
A1201#//#1234#//#Ahmad Walid#//#+962771983925#//#3000.000000#//#
B1202#//#5678#//#Farid Yasin#//#+962701981759#//#2000.000000#//#
C1203#//#9101#//#Tariq Majd#//#+962790123456#//#50000.000000#//#
```

### `Users.txt`

```text
UserName#//#Password#//#Permissions#//#
```

```text
Admin#//#1234#//#-1#//#
User1#//#1111#//#31#//#
User2#//#2222#//#17#//#
```

> ⚠️ **Important:** `Users.txt` must exist with at least one user (like the `Admin` line above) before the first run, otherwise nobody can log in. `Clients.txt` is created automatically when the first client is added.

---

## 👤 Client Information

Every client contains:

* 🔢 **Account Number**
* 🔐 **PIN Code**
* 👤 **Full Name**
* 📱 **Phone Number**
* 💰 **Account Balance**

---

## 🧠 What I Practiced

```text
C++
├── Functions
├── Structs
├── Vectors
├── Enums
├── Loops
├── Input Validation
├── File Handling
├── String Manipulation
├── Data Serialization
├── Login System
├── Bitwise Permissions (flags & masks)
├── Banking Transactions (Deposit / Withdraw)
└── Menu-Driven Programs
```

I also practiced separating the program into smaller functions instead of putting everything inside `main()`.

---

## 🏗️ Code Structure

### Structs

```cpp
stClient   // a bank client
stUsers    // a system user (name, password, permissions)
```

### File Handling

```cpp
LoadClientsDataFromFile()   LoadUsersDataFromFile()
AddDataLineToFile()
SaveClientDataToFile()      SaveUsersDataToFile()
```

### Client Operations

```cpp
AddNewClient()
DeleteClientByAccountNumber()
UpdateClientByAccountNumber()
FindClientPrint()
```

### Transactions

```cpp
DepositFunction()
WithdrawFunction()
CheckAmountDeposit()
CheckAmountWithdraw()
TotallBalances()
```

### Users & Permissions

```cpp
Login() / LoginUser() / LoginUsersCheck()
CheckPermissions()
ReadPermissionsToSet()
AddNewUser() / DeleteUser() / UpdateUser() / FindUser()
AccessDeniedScreen()
```

### Data Conversion

```cpp
SplitString()
ConvertLinetoRecord()        ConvertLinetoRecordUsers()
ConvertRecordToLine()        ConvertRecordToLineUsers()
```

---

## 🔄 How It Works

```text
Start
  ↓
Login Screen ──(wrong credentials)──→ try again
  ↓
Main Menu
  ↓
Choose an Operation ──(no permission)──→ Access Denied
  ↓
Perform the Operation
  ↓
Return to Main Menu
  ↓
Logout → back to Login Screen
```

---

## 🛠️ Technologies

* **C++11+**
* `iostream`
* `fstream`
* `vector`
* `string`
* `iomanip`
* `cctype`
* `limits`

---

## ▶️ Build & Run

### Linux / macOS

```bash
g++ code.cpp
./a.out
```

Run it from the same folder that contains `Clients.txt` and `Users.txt`.

### Windows

Replace every:

```cpp
system("clear");
```

with:

```cpp
system("cls");
```

---

## 📌 Current Improvements

Some improvements I plan to explore in the future:

* ✅ Better account number validation
* ✅ Stronger PIN validation
* 🔐 Hash/encrypt PINs and user passwords instead of storing them as plain text
* 🛡️ Prevent deleting the `Admin` user / the last user with full access
* 💵 Fix deposit/withdraw amounts so they accept cents/decimals, not just whole numbers
* 🗂️ Split the project into separate header and source files
* 🎨 Improve the console interface
* 📊 Add more banking features (transaction history, transfers between accounts)

---

## 📚 Sample Data

### `Clients.txt`

```text
A1201#//#1234#//#Ahmad Walid#//#+962771983925#//#3000.000000#//#
B1202#//#5678#//#Farid Yasin#//#+962701981759#//#2000.000000#//#
C1203#//#9101#//#Tariq Majd#//#+962790123456#//#50000.000000#//#
D1204#//#5635#//#Faris Ayman#//#+962793847083#//#6000.000000#//#
E1205#//#4174#//#Khalid Amir#//#+962704012290#//#70000.000000#//#
F1206#//#3364#//#Omar Raif#//#+962707914911#//#5000.000000#//#
```

### `Users.txt`

```text
Admin#//#1234#//#-1#//#
User1#//#1111#//#31#//#
User2#//#2222#//#17#//#
User3#//#3333#//#7#//#
```

---

## 🎯 Project Goal

The main goal of this project was not just to build a bank management system, but to **strengthen my C++ problem-solving skills and learn how to structure a real console application** — now including authentication and role-based access control.

---

## ⭐ If You Like It

Feel free to explore the code, try the application, and check out the different features.

**More projects coming soon! 🚀**

---

### 👨‍💻 Built with C++

**Learning → Practicing → Building → Improving**
