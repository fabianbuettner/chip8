#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode8xy5 : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode8xy5(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
