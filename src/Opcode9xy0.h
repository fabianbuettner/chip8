#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode9xy0 : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
    std::uint8_t y = 0;

public:
    Opcode9xy0(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
