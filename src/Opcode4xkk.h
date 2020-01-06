#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode4xkk : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode4xkk(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
