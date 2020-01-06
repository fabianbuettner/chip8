#include "OpcodeFx07.h"

#include <iomanip>
#include <sstream>

OpcodeFx07::OpcodeFx07(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx07::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    cpu.v[x] = cpu.delay_timer;
    return true;
}

std::string OpcodeFx07::getDescription(void)
{
    std::stringstream stream;
    stream << "The value of DT is placed into Vx";
    return stream.str();
}

std::string OpcodeFx07::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", DT";
    return stream.str();
}
