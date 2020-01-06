#include "Opcode8xy6.h"

#include <iomanip>
#include <sstream>

Opcode8xy6::Opcode8xy6(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy6::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    cpu.v[0xf] = cpu.v[x] & 0x01;
    cpu.v[y] = cpu.v[x] >> 1;
    return true;
}

std::string Opcode8xy6::getDescription(void)
{
    std::stringstream stream;
    stream << "If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.";
    return stream.str();
}

std::string Opcode8xy6::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "SHR V" << std::hex << static_cast<std::uint16_t>(y) << ", V" << static_cast<std::uint16_t>(x);
    return stream.str();
}
