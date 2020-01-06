#include "OpcodeFx29.h"

#include <iomanip>
#include <sstream>

OpcodeFx29::OpcodeFx29(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx29::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    cpu.i = sprite_address + cpu.v[x] * 5;
    return true;
}

std::string OpcodeFx29::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Set I = location of sprite for digit V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx29::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD F, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
