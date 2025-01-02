#include "cli.h"
#include <iostream>
#include <sstream>

CLI::CLI() : table("default_table") {}

void CLI::start() {
    std::cout << "B-Tree-Based Database!" << std::endl;
    std::cout << "Type your commands below (type EXIT to quit):" << std::endl;

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "EXIT") {
            std::cout << "Exiting database!" << std::endl;
            break;
        }

        processCommand(command);
    }
}

void CLI::processCommand(const std::string& command) {
    std::istringstream commandStream(command);
    std::string action;
    commandStream >> action;

    if (action == "INSERT") {
        handleInsert(command);
    } else if (action == "SELECT") {
        handleSelect(command);
    } else if (action == "DELETE") {
        handleDelete(command);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

void CLI::handleInsert(const std::string& command) {
    int id;
    char name[50];
    int age;

    if (sscanf(command.c_str(), "INSERT INTO table (id, name, age) VALUES (%d, \"%49[^\"]\", %d)", &id, name, &age) == 3) {
        Row row(id, name, age);
        if (table.insertRow(row)) {
            std::cout << "Row inserted successfully." << std::endl;
        } else {
            std::cerr << "Failed to insert row." << std::endl;
        }
    } else {
        std::cerr << "Invalid INSERT command syntax." << std::endl;
    }
}

void CLI::handleSelect(const std::string& command) {
    int id;
    if (sscanf(command.c_str(), "SELECT * FROM table WHERE id = %d", &id) == 1) {
        auto row = table.selectRow(id);
        if (row) {
            std::cout << "Row found: ID=" << row->id << ", Name=" << row->name << ", Age=" << row->age << std::endl;
        } else {
            std::cerr << "Row with ID=" << id << " not found." << std::endl;
        }
    } else {
        std::cerr << "Invalid SELECT command syntax." << std::endl;
    }
}

void CLI::handleDelete(const std::string& command) {
    int id;
    if (sscanf(command.c_str(), "DELETE FROM table WHERE id = %d", &id) == 1) {
        if (table.deleteRow(id)) {
            std::cout << "Row deleted successfully." << std::endl;
        } else {
            std::cerr << "Row with ID=" << id << " not found." << std::endl;
        }
    } else {
        std::cerr << "Invalid DELETE command syntax." << std::endl;
    }
}
