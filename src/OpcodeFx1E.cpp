#include "OpcodeFx1E.h"

#include <iomanip>
#include <sstream>

OpcodeFx1E::OpcodeFx1E(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx1E::execute(void)
{
    cpu.I += cpu.V[x];
    if (cpu.I > 0xfff) {
        cpu.V[0xf] = 1;
    } else {
        cpu.V[0xf] = 0;
    }
    return true;
}

std::string OpcodeFx1E::getDescription(void)
{
    std::stringstream stream;
    stream << std::hex << "The values of I and Vx are added, and the results are stored in I.";
    return stream.str();
}

std::string OpcodeFx1E::getMnemonic(void)
{
    std::stringstream stream;
    stream << "ADD I, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
