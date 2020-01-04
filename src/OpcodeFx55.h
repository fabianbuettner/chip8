#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeFx55 : public Opcode {
private:
    Cpu& cpu;
    std::uint16_t x = 0;
public:
    OpcodeFx55(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
