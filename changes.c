**Struct Change — `firstName` field size**
```c
// Original
char firstName[10];

// Modified
char firstName[15];
```
Increased the first name buffer from 10 to 15 characters to accommodate longer names.

**File Initialization — `initializeFile()`**
This is a **brand new function** not present in the original. It checks if `credit.dat` exists; if not, it creates the file and pre-fills it with 100 blank records. The original required the file to already exist and would simply exit if it didn't.

**Expanded Menu — from 5 options to 11**

| Original | Modified |
|---|---|
| 1. Store text file | 1. Add Account |
| 2. Update account | 2. View All Accounts |
| 3. Add new account | 3. Search Account |
| 4. Delete account | 4. Deposit Money |
| 5. Exit | 5. Withdraw Money |
| | 6. Transfer Money |
| | 7. Update Balance |
| | 8. Delete Account |
| | 9. Generate Text Report |
| | 10. Statistics |
| | 11. Exit |

**New Functions Added**

**`viewAccounts()`** — Loops through all 100 records and prints every active account in a formatted table. The original had no dedicated view-all feature.

**`searchAccount()`** — Lets the user look up a single account by number and displays its full details. The original had no search feature.

**`deposit()`** — Dedicated function that adds a positive amount to a specific account's balance with validation.

**`withdraw()`** — Dedicated function that subtracts an amount from the balance, with an **insufficient funds check** — a safety guard the original lacked.

**`transfer()`** — Entirely new. Moves funds between two accounts atomically: deducts from sender, adds to receiver, with validation on both accounts and balance sufficiency.

**`statistics()`** — Scans all records and reports the total number of active accounts, total balance across all accounts, and average balance per account.

**`addAccount()` — Cleaner Input**
The original `newRecord()` used a single `scanf` to read last name, first name, and balance together (`scanf("%14s%9s%lf", ...)`). The modified version uses **separate prompts** for each field, making it more user-friendly.

**`updateAccount()` vs `updateRecord()`**
The original printed the account details before and after the transaction. The modified version simply shows the **current balance**, asks for the amount, and confirms the update — cleaner and less verbose.

**Error Handling & UX Improvements**
- The modified code uses `return` early from functions on errors (e.g., account not found, insufficient balance) instead of nested `if-else` blocks, making the logic easier to follow.
- Success/failure messages are clearer ("Account Added Successfully!", "Insufficient Balance!", etc.).
- The menu is displayed with a formatted header (`BANK MANAGEMENT SYSTEM`) for better readability.