#pragma once

#include "Cpu.h"
#include "Opcode.h"

class Opcode7xkk : public Opcode {
private:
    Cpu& cpu;
    std::uint8_t x = 0;
    std::uint16_t kk = 0;
public:
    Opcode7xkk(Cpu& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
