#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class OpcodeCxkk : public Opcode {
private:
    CpuChip8& cpu;

public:
    OpcodeCxkk(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
