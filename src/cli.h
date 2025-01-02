#ifndef CLI_H
#define CLI_H

#include <string>
#include "table.h"

class CLI {
public:
    CLI();
    void start();

private:
    Table table;

    void processCommand(const std::string& command);
    void handleInsert(const std::string& command);
    void handleSelect(const std::string& command);
    void handleDelete(const std::string& command);
};

#endif // CLI_H
