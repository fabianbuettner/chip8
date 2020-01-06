#include "OpcodeFx33.h"

#include <iomanip>
#include <sstream>

OpcodeFx33::OpcodeFx33(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx33::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t value = cpu.v[x];
    cpu.memory[cpu.i + 2] = value % 10;
    value /= 10;
    cpu.memory[cpu.i + 1] = value % 10;
    value /= 10;
    cpu.memory[cpu.i] = value % 10;
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
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD B, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
