#include "Opcode8xy1.h"

#include <iomanip>
#include <sstream>

Opcode8xy1::Opcode8xy1(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy1::execute(void)
{
    cpu.V[x] |= cpu.V[y];
    return true;
}

std::string Opcode8xy1::getDescription(void)
{
    std::stringstream stream;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(x) << " OR V" << static_cast<std::uint16_t>(y) << ".";
    return stream.str();
}

std::string Opcode8xy1::getMnemonic(void)
{
    std::stringstream stream;
    stream << "OR V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
