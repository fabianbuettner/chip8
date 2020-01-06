#include "Opcode8xy5.h"

#include <iomanip>
#include <sstream>

Opcode8xy5::Opcode8xy5(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy5::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    std::uint8_t borrow = cpu.v[x] >= cpu.v[y];
    //cpu.v[x] = abs(cpu.v[x] - cpu.v[y]);
    cpu.v[x] = cpu.v[x] - cpu.v[y];
    cpu.v[0xf] = borrow;
    return true;
}

std::string Opcode8xy5::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(x) << " - V" << static_cast<std::uint16_t>(y) << ", set VF = NOT borrow";
    return stream.str();
}

std::string Opcode8xy5::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "SUB V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
