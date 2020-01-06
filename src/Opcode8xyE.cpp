#include "Opcode8xyE.h"

#include <iomanip>
#include <sstream>

Opcode8xyE::Opcode8xyE(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xyE::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    cpu.v[0xf] = cpu.v[x] >> 7;
    cpu.v[y] = cpu.v[x] << 1;
    return true;
}

std::string Opcode8xyE::getDescription(void)
{
    std::stringstream stream;
    stream << "If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.";
    return stream.str();
}

std::string Opcode8xyE::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "SHL V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
