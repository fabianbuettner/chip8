#include "Opcode8xy7.h"

#include <iomanip>
#include <sstream>

Opcode8xy7::Opcode8xy7(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy7::execute(void)
{
    cpu.V[0xf] = cpu.V[y] > cpu.V[x];
    cpu.V[x] = cpu.V[y] - cpu.V[x];
    return true;
}

std::string Opcode8xy7::getDescription(void)
{
    std::stringstream stream;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(y) << " - V" << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string Opcode8xy7::getMnemonic(void)
{
    std::stringstream stream;
    stream << "SUBN V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
