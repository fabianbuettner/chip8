#include "Opcode8xy0.h"

#include <iomanip>
#include <sstream>

Opcode8xy0::Opcode8xy0(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy0::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    cpu.v[x] = cpu.v[y];
    return true;
}

std::string Opcode8xy0::getDescription(void)
{
    std::stringstream stream;
    stream << "Stores the value of register Vy in register Vx.";
    return stream.str();
}

std::string Opcode8xy0::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
