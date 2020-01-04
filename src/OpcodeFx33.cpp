#include "OpcodeFx33.h"

#include <iomanip>
#include <sstream>

OpcodeFx33::OpcodeFx33(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx33::execute(void)
{
    std::uint8_t value = cpu.V[x];
    cpu.program[cpu.I + 2] = value % 10;
    value /= 10;
    cpu.program[cpu.I + 1] = value % 10;
    value /= 10;
    cpu.program[cpu.I] = value % 10;
    return true;
}

std::string OpcodeFx33::getDescription(void)
{
    std::stringstream stream;
    stream << "The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2";
    return stream.str();
}

std::string OpcodeFx33::getMnemonic(void)
{
    std::stringstream stream;
    stream << "LD B, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
