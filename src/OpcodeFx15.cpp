#include "OpcodeFx15.h"

#include <iomanip>
#include <sstream>

OpcodeFx15::OpcodeFx15(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx15::execute(void)
{
    cpu.delay_timer = cpu.V[0];
    return true;
}

std::string OpcodeFx15::getDescription(void)
{
    std::stringstream stream;
    stream << "Set delay timer = V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx15::getMnemonic(void)
{
    std::stringstream stream;
    stream << "LD DT, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
