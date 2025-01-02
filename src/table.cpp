#include "table.h"
#include <iostream>
#include <stdexcept>

// Constructor
Table::Table(const std::string& tableName)
    : tableName(tableName), index(2),
      dataFilePath("data/" + tableName + "_data.db"),
      indexFilePath("data/" + tableName + "_index.db") {
    loadTable();
}

// Destructor
Table::~Table() {
    saveTable();
    if (dataFile.is_open()) {
        dataFile.close();
    }
}

// Load table data and index from disk
void Table::loadTable() {

    dataFile.open(dataFilePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!dataFile) {
        dataFile.open(dataFilePath, std::ios::out); 
        dataFile.close();
        dataFile.open(dataFilePath, std::ios::in | std::ios::out | std::ios::binary);
    }


    std::ifstream indexFile(indexFilePath, std::ios::binary);
    if (indexFile) {
        index.loadFromDisk(indexFilePath);
        indexFile.close();
    }
}


void Table::saveTable() {

    index.saveToDisk(indexFilePath);
}


bool Table::insertRow(const Row& row) {
    if (index.search(row.id) != -1) {
        std::cerr << "Error: Duplicate primary key (" << row.id << ")." << std::endl;
        return false;
    }

    int offset = writeRowToFile(row);
    index.insert(row.id, offset);
    return true;
}


std::optional<Row> Table::selectRow(int id) {
    int offset = index.search(id);
    if (offset == -1) {
        return std::nullopt;
    }

    return readRowFromFile(offset);
}


bool Table::deleteRow(int id) {
    int offset = index.search(id);
    if (offset == -1) {
        return false;
    }

    Row row = readRowFromFile(offset).value();
    row.id = -1; 
    dataFile.seekp(offset, std::ios::beg);
    dataFile.write(reinterpret_cast<char*>(&row), sizeof(Row));

    return true;
}

int Table::writeRowToFile(const Row& row) {
    dataFile.seekp(0, std::ios::end);
    int offset = dataFile.tellp();
    dataFile.write(reinterpret_cast<const char*>(&row), sizeof(Row));
    return offset;
}


std::optional<Row> Table::readRowFromFile(int offset) {
    dataFile.seekg(offset, std::ios::beg);
    Row row;
    dataFile.read(reinterpret_cast<char*>(&row), sizeof(Row));

    if (row.id == -1) {
        return std::nullopt; 
    }

    return row;
}
