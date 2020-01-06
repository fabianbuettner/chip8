#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode6xkk : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode6xkk(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
