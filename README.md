# 💳 Payment Application (Embedded Systems C Project)

A highly structured, modular **C-based Payment System** simulating a real-world credit card transaction environment. This project demonstrates strict adherence to industrial C-programming standards, defensive programming, structural modularity, and persistent file-based data handling crucial for **Embedded Systems** and automotive software development.

---

## 🛠️ Used Technologies & Systems Concepts
- **Programming Language:** ANSI C (100%) - Employing strict memory management and defensive design.
- **Data Persistence:** File I/O Handling (Flat-file Database System).
- **Development Environment:** Microsoft Visual Studio (MSVC Compiler).
- **Embedded C Concepts Applied:**
  - **Modular Architecture:** Complete decoupling between layers via abstract interfaces.
  - **Custom Data Types:** Intensive usage of standard typedefs, custom structs, and type-safe `enums` for function state returns.
  - **Defensive Programming:** Input null-pointer checking, string boundary limits, and strict value range constraints.
  - **File Stream Management:** Secure opening, parsing, and closing of file streams to prevent memory leaks and data corruption.

---

## 📁 Project Structure (Architecture)

The repository follows a clean layered structure with a persistent file-based database located at the project root directory:

```text
paymentApplication/
├── Project1/
│   ├── Card/               # Card Module (Data Acquisition)
│   │   ├── card.c          # Implementation of card operations
│   │   └── card.h          # Card structure & prototypes
│   ├── Terminal/           # Terminal Module (Validation Logic)
│   │   ├── terminal.c      # Verification of expiry, amounts & limits
│   │   └── terminal.h      # Terminal parameters & configurations
│   ├── Server/             # Server Module (Database Logic Engine)
│   │   ├── server.c        # Contains parsing algorithms & File I/O functions
│   │   └── server.h        # Server state definitions & structures
│   ├── Application/        # Application Layer (Orchestration)
│   │   ├── app.c           # Master flow control sequence
│   │   └── app.h           # Main program interface
│   ├── main.c              # Application Entry Point
│   ├── Accounts DB.txt      # 💾 Central Database (Registered PANs & Balances)
│   ├── Transactions DB.txt  # 📜 Persistence Ledger (Appended Transaction Logs)
│   └── .gitignore          # Excludes build artifacts (obj, debug, etc.)
└── Project1.sln            # Visual Studio Solution File
```

---

## 🔀 System Logic Flowchart

The following diagram illustrates the structural pipeline and verification sequence executed during a single payment cycle:

```mermaid
graph TD
    A([Start Transaction]) --> B[Get Card Data: Name, PAN, Expiry]
    B --> C{Is Card Expired?}
    C -- Yes --> D[Declined: EXPIRED_CARD]
    C -- No --> E[Get Transaction Amount]
    E --> F{Is Amount > Max Limit?}
    F -- Yes --> G[Declined: EXCEED_MAX_AMOUNT]
    F -- No --> H[Send Data to Server]
    H --> I{Does PAN Exist in Accounts DB.txt?}
    I -- No --> J[Declined: ACCOUNT_NOT_FOUND]
    I -- Yes --> K{Is Balance Sufficient?}
    K -- No --> L[Declined: LOW_BALANCE]
    K -- Yes --> M[Approve: Update Database Balance]
    M --> N[Append Log to Transactions DB.txt]
    D & G & J & L & N --> O([End Transaction])
    
    style A fill:#4CAF50,stroke:#333,stroke-width:2px,color:#fff
    style O fill:#f44336,stroke:#333,stroke-width:2px,color:#fff
    style M fill:#8BC34A,stroke:#333,stroke-width:1px
```

---

## 🧠 Core Algorithms & Validation Logic

The application implements standard financial check routines across three isolated validation engines:

### 1. Card Module Algorithm
- **Data Capture:** Prompts and grabs exact string lengths from stdin.
- **Constraints Enforcement:**
  - Cardholder Name: Exactly `20 - 24` alphabetic characters.
  - Primary Account Number (PAN): Exactly `16 - 19` numeric characters.
  - Expiry Date: Strict format `MM/YY` (5 chars total).

### 2. Terminal Module Algorithm
- **Date Comparison:** Compares Card Expiration Date (`MM/YY`) against the current System Date (`MM/YYYY`).
  - *Algorithm:* Extracts and converts month/year substrings into numerical integers to evaluate logical inequalities.
- **Limit Checker:** Evaluates if `transAmount <= maxTransAmount`.

### 3. Server Module Algorithm (File-Based Engine)
- **File-Based Account Verification:** The server utilizes file streams (`fopen`) in read mode (`"r"`) to search `Accounts DB.txt`. It loops line-by-line using string parsing techniques to locate the matching `PAN` and retrieve its corresponding balance securely.
- **Secure Ledger Auditing:** Upon completing a transaction, the server opens `Transactions DB.txt` in append mode (`"a"`). It appends a complete real-time record (Sequence ID, PAN, Transaction Status, and Amount) ensuring long-term data persistence.

---

## 🧪 Comprehensive Testing Matrix (Verification & Validation)

To guarantee the reliability of the system and ensure strict boundary configurations, the following test matrix was executed covering both **Happy Paths** and **Edge Cases**:

### 1. Card Module Tests

| Test Case ID | Scenario / Input | Expected Status | Actual Result | Pass/Fail |
| :--- | :--- | :--- | :--- | :---: |
| **TC_CARD_01** | Valid Name, PAN (16 digits), Expiry (05/28) | `CARD_OK` | `CARD_OK` | ✅ Pass |
| **TC_CARD_02** | Name less than 20 characters (e.g., "John Doe") | `WRONG_NAME` | `WRONG_NAME` | ✅ Pass |
| **TC_CARD_03** | PAN with invalid format/length (e.g., "123") | `WRONG_PAN` | `WRONG_PAN` | ✅ Pass |

### 2. Terminal Module Tests

| Test Case ID | Scenario / Input | Expected Status | Actual Result | Pass/Fail |
| :--- | :--- | :--- | :--- | :---: |
| **TC_TERM_01** | Valid amount within limits and unexpired card | `TERMINAL_OK` | `TERMINAL_OK` | ✅ Pass |
| **TC_TERM_02** | Expired Card (Card: 03/22 vs Terminal: 08/25) | `EXPIRED_CARD` | `EXPIRED_CARD` | ✅ Pass |
| **TC_TERM_03** | Amount exceeds Max Limit (Amount: 15k, Limit: 10k) | `EXCEED_MAX_AMOUNT` | `EXCEED_MAX_AMOUNT` | ✅ Pass |

### 3. Server Module Tests

| Test Case ID | Scenario / Input | Expected Status | Actual Result | Pass/Fail |
| :--- | :--- | :--- | :--- | :---: |
| **TC_SERV_01** | Valid transaction, PAN found, sufficient balance | `SERVER_OK` (APPROVED) | `SERVER_OK` | ✅ Pass |
| **TC_SERV_02** | PAN not registered inside `Accounts DB.txt` | `ACCOUNT_NOT_FOUND` | `ACCOUNT_NOT_FOUND` | ✅ Pass |
| **TC_SERV_03** | PAN found but balance is insufficient | `LOW_BALANCE` | `LOW_BALANCE` | ✅ Pass |

---

## 🚀 How to Build and Run

1. Clone the repository to your desktop machine:
   ```bash
   git clone https://github.com
   ```
2. Open `Project1.sln` inside **Microsoft Visual Studio**.
3. Press `Ctrl + F5` or click **Local Windows Debugger** to compile and launch the interactive CLI environment.

---

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## Author
**Mahmoud Saleh**
* Embedded Systems Engineer
* [GitHub Profile](https://github.com/Mahmoud976)
* [LinkedIn Profile](https://www.linkedin.com/in/mahmoud-m-saleh/)
