#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode8xyE : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
    std::uint8_t y = 0;
public:
    Opcode8xyE(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};