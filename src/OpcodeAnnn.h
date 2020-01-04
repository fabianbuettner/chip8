#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeAnnn : public Opcode {
private:
    Cpu& cpu;
    std::uint16_t nnn = 0;
public:
    OpcodeAnnn(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
