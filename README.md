# B-Trees-Based Database

A minimal database system built in C++ that supports:
- Disk-backed storage
- A B-tree-based index for efficient lookups
- Basic SQL-like commands for interaction via a Command-Line Interface (CLI)

## Table of Contents
- [Features](#features)
  - [Core Functionalities](#core-functionalities)
  - [Data Persistence](#data-persistence)
  - [Command-Line Interface](#command-line-interface)
- [How to Build and Run](#how-to-build-and-run)
  - [Prerequisites](#prerequisites)
  - [Build](#build-instructions)
  
- [Project Directory Structure](#project-directory-structure)
- [Future Enhancements (TODO)](#future-enhancements-todo)
- [Contributing](#contributing)


## Features

### Core Functionalities
1. **CREATE TABLE**: Define a schema with column names and types (currently supports a single table).
2. **INSERT**: Add rows to the table.
3. **SELECT**: Retrieve rows using primary key lookup.
4. **DELETE**: Remove rows using primary key lookup.

### Data Persistence
- **Disk-Backed Storage**:
  - Rows are stored in a binary file.
  - Index is stored persistently using a serialized B-Tree structure.
- Data and index files are saved between sessions and automatically loaded on startup.

### Command-Line Interface
Interact with the database using SQL-like commands:
- **Insert a Row**:
  ```sql
  INSERT INTO table (id, name, age) VALUES (1, "SomeName", 25);
  ```

- **Select a Row**:
  ```sql
  SELECT * FROM table WHERE id = 1;
  ```

- **Delete a Row**:
  ```sql
  DELETE FROM table WHERE id = 1;
  ```

- **Exit from CLI**:
  ```sql
  EXIT
  ```

# How to Build and Run

## Prerequisites
To build and run the project, you will need:
- A C++ compiler with **C++17 support** (e.g., GCC or Clang).

## Build Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/btrees-based-database.git
   cd btrees-based-database
   make clean
   ```
2. **Build and Run**:
   ```bash
   make
   ./B-Trees-Based-Database
   ```

# Project Directory Structure

Project organization is as follows:

```csharp
mini_db/
├── src/
│   ├── main.cpp           # Entry point
│   ├── btree.cpp          # B-tree implementation
│   ├── btree.h            # B-tree interface
│   ├── table.cpp          # Table management
│   ├── table.h            # Table interface
│   ├── cli.cpp            # Command-line interface
│   ├── cli.h              # CLI interface
├── data/
│   ├── table_data.db      # Persistent table data
│   ├── table_index.db     # Persistent B-tree index
├── README.md              # Documentation
├── Makefile               # Build script
```

# Future Enhancements (TODO)

The following features are planned for future releases:

- **Support Multiple Tables**:
  - Add commands like `CREATE TABLE` and `USE TABLE` to manage multiple tables.
  
- **Transactions**:
  - Implement `BEGIN TRANSACTION`, `COMMIT`, and `ROLLBACK` with write-ahead logging.
  
- **Query Optimization**:
  - Support range queries like `SELECT * FROM table WHERE id > 5`.
  - Add support for text-based queries.
  
- **Error Handling**:
  - Improve validation for user input and table schema consistency.
  
- **Concurrency**:
  - Add support for multi-threaded operations.
  
- **Testing**:
  - Build a test suite using Google Test for unit and integration tests.

---

# Contributing

We welcome contributions! Please feel free to:
- Fork the repository
- Submit pull requests
- Report bugs or suggest features in the issue tracker

---




