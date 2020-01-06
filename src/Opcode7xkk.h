#pragma once

#include "CpuChip8.h"
#include "Opcode.h"

class Opcode7xkk : public Opcode {
private:
    CpuChip8& cpu;

public:
    Opcode7xkk(CpuChip8& cpu);

    bool execute(void) final;
    std::string getDescription(void) final;
    std::string getMnemonic(void) final;
};
