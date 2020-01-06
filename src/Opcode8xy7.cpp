#include "Opcode8xy7.h"

#include <iomanip>
#include <sstream>

Opcode8xy7::Opcode8xy7(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy7::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    std::uint8_t borrow = cpu.v[y] >= cpu.v[x];
    //cpu.v[x] = abs(cpu.v[y] - cpu.v[x]);
    cpu.v[x] = cpu.v[y] - cpu.v[x];
    cpu.v[0xf] = borrow;
    return true;
}

std::string Opcode8xy7::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(y) << " - V" << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string Opcode8xy7::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "SUBN V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
