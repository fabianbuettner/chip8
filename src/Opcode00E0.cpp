#include "Opcode00E0.h"

Opcode00E0::Opcode00E0(Cpu& cpu)
    : cpu { cpu }
{
}

bool Opcode00E0::execute(void)
{
    std::fill(std::begin(cpu.display), std::end(cpu.display), 0);
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
