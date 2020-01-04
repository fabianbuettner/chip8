#include "Opcode8xy6.h"

#include <iomanip>
#include <sstream>

Opcode8xy6::Opcode8xy6(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy6::execute(void)
{
    cpu.V[0xf] = cpu.V[x] & 0x01;
    cpu.V[y] = cpu.V[x] >> 1;
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
    stream << "SHR V" << std::hex << static_cast<std::uint16_t>(y) << ", V" << static_cast<std::uint16_t>(x);
    return stream.str();
}
