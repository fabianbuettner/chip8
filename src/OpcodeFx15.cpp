#include "OpcodeFx15.h"

#include <iomanip>
#include <sstream>

OpcodeFx15::OpcodeFx15(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx15::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    cpu.delay_timer = cpu.v[0];
    return true;
}

std::string OpcodeFx15::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Set delay timer = V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx15::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD DT, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
