#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode9xy0 : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode9xy0(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
