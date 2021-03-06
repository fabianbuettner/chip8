#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class OpcodeEx9E : public Opcode {
private:
    CpuChip8& cpu;

public:
    OpcodeEx9E(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
