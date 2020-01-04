#pragma once

#include "Cpu.h"
#include <iostream>
#include <vector>

class Disassembler {
public:
    Cpu& cpu;
public:
    Disassembler(Cpu& cpu);
    ~Disassembler(void);
    friend std::ostream& operator<<(std::ostream& os, Disassembler& disassembler);
};
