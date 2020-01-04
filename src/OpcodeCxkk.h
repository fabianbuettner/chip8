#pragma once

#include "Cpu.h"
#include "Opcode.h"

class OpcodeCxkk : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
    std::uint8_t kk = 0;
    std::uint8_t random_byte = 0;
public:
    OpcodeCxkk(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};