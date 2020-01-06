#include "OpcodeFx18.h"

#include <iomanip>
#include <sstream>

OpcodeFx18::OpcodeFx18(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx18::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    cpu.sound_timer = cpu.v[0];
    return true;
}

std::string OpcodeFx18::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Set sound timer = V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx18::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD ST, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
