#include "OpcodeFx1E.h"

#include <iomanip>
#include <sstream>

OpcodeFx1E::OpcodeFx1E(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx1E::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    cpu.i += cpu.v[x];
    if (cpu.i > 0xfff) {
        cpu.v[0xf] = 1;
    } else {
        cpu.v[0xf] = 0;
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
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "ADD I, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
