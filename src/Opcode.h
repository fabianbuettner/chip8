#pragma once

#include <iostream>
#include <string>

class Opcode {
public:
    virtual bool execute()
    {
        std::cout << "Opcode::execute() not implemented!" << std::endl;
        return false;
    };
    virtual std::string getDescription(void) = 0;
    virtual std::string getMnemonic(void) = 0;
};
