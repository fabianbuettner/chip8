#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode2nnn : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode2nnn(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
