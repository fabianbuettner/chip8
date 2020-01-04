#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeEx9E : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;

public:
    OpcodeEx9E(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
