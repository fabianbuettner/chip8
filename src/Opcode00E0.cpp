#include "Opcode00E0.h"

Opcode00E0::Opcode00E0(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode00E0::execute(void)
{
    std::fill(std::begin(cpu.display.memory), std::end(cpu.display.memory), 0);
    cpu.display.refresh();
    return true;
}

std::string Opcode00E0::getDescription(void)
{
    return "Clear the display.";
}

std::string Opcode00E0::getMnemonic(void)
{
    std::stringstream stream;
    stream << "CLS";
    return stream.str();
}
