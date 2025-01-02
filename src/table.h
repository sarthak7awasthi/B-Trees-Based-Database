#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>
#include <optional>
#include <cstring>
#include "btree.h"

struct Row {
    int id;                // Primary key
    char name[50];         // Fixed-size char array for name
    int age;               // Age column

    Row(int id = -1, const std::string& name = "", int age = 0) : id(id), age(age) {
        strncpy(this->name, name.c_str(), sizeof(this->name) - 1);
        this->name[sizeof(this->name) - 1] = '\0'; 
    }
};

class Table {
public:
    Table(const std::string& tableName);
    ~Table();

    bool insertRow(const Row& row);
    std::optional<Row> selectRow(int id);
    bool deleteRow(int id);

    void loadTable(); // Load data and index from disk
    void saveTable(); // Save data and index to disk

private:
    std::string tableName;       
    std::fstream dataFile;      
    BTree index;               
    const std::string dataFilePath;  
    const std::string indexFilePath; 

    int writeRowToFile(const Row& row); // Write a row to the file and return its offset
    std::optional<Row> readRowFromFile(int offset); // Read a row from the file at the given offset
};

#endif // TABLE_H
