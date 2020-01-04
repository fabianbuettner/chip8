#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode1nnn : public Opcode {
private:
    Cpu& cpu;
    std::uint16_t nnn = 0;
public:
    Opcode1nnn(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
