#pragma once

#include <iostream>
#include <string>

struct Opcode {
protected:
    std::uint16_t opcode = 0;

public:
    virtual bool execute()
    {
        std::cout << "Opcode::execute() not implemented!" << std::endl;
        return false;
    };
    virtual std::string getDescription(void) = 0;
    virtual std::string getMnemonic(void) = 0;
    virtual void setOpcode(std::uint16_t opcode) { this->opcode = opcode; }
};
