#include "Opcode8xyE.h"

#include <iomanip>
#include <sstream>

Opcode8xyE::Opcode8xyE(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xyE::execute(void)
{
    cpu.V[0xf] = cpu.V[x] >> 7;
    cpu.V[y] = cpu.V[x] << 1;
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
    stream << "SHL V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
