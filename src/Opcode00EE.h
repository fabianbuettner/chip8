#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode00EE : public Opcode {
private:
    Cpu& cpu;
public:
    Opcode00EE(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
