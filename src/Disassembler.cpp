#include "Disassembler.h"
#include "utilities.h"

#include <iomanip>

Disassembler::Disassembler(Cpu& cpu)
    : cpu { cpu }
{
}

Disassembler::~Disassembler(void)
{
}

std::ostream& operator<<(std::ostream& os, Disassembler& disassembler)
{
    return disassembler.cpu.printDisassembly(os);
}
