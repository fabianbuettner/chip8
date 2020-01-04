#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeFx29 : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
public:
    OpcodeFx29(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
