#include "Opcode6xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode6xkk::Opcode6xkk(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    kk = (cpu.opcode & 0xff);
}

bool Opcode6xkk::execute(void)
{
    cpu.V[x] = kk;
    return true;
}

std::string Opcode6xkk::getDescription(void)
{
    std::stringstream stream;
    stream << "The interpreter puts the value kk into register Vx.";
    return stream.str();
}

std::string Opcode6xkk::getMnemonic(void)
{
    std::stringstream stream;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
