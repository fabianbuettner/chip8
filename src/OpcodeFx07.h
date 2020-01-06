#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class OpcodeFx07 : public Opcode {
private:
    CpuChip8& cpu;

public:
    OpcodeFx07(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
