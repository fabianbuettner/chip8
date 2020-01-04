#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode00E0 : public Opcode {
private:
    Cpu& cpu;
public:
    Opcode00E0(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
