#include "Opcode8xy2.h"

#include <iomanip>
#include <sstream>

Opcode8xy2::Opcode8xy2(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy2::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    cpu.v[x] &= cpu.v[y];
    return true;
}

std::string Opcode8xy2::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(x) << " AND V" << static_cast<std::uint16_t>(y) << ".";
    return stream.str();
}

std::string Opcode8xy2::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "AND V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
