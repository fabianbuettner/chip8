#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeDxyn : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
    std::uint8_t y = 0;
    std::uint8_t n = 0;

public:
    OpcodeDxyn(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
