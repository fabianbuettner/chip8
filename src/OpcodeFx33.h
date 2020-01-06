#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class OpcodeFx33 : public Opcode {
private:
    CpuChip8& cpu;

public:
    OpcodeFx33(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
