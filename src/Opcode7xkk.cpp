#include "Opcode7xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode7xkk::Opcode7xkk(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    kk = cpu.opcode & 0xff;
}

bool Opcode7xkk::execute(void)
{
    cpu.V[x] += kk;
    return true;
}

std::string Opcode7xkk::getDescription(void)
{
    std::stringstream stream;
    stream << "Adds the value " << int_to_hexstring(kk, 2) << " to the value of register V" << static_cast<std::uint16_t>(x) << ", then stores the result in Vx.";
    return stream.str();
}

std::string Opcode7xkk::getMnemonic(void)
{
    std::stringstream stream;
    stream << "ADD V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
