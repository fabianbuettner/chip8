#include "OpcodeFx65.h"

#include <iomanip>
#include <sstream>

OpcodeFx65::OpcodeFx65(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx65::execute(void)
{
    for (std::uint8_t i = 0; i <= x; i++) {
        cpu.V[i] = cpu.program[cpu.I + i];
    }
    cpu.I += x + 1;
    return true;
}

std::string OpcodeFx65::getDescription(void)
{
    std::stringstream stream;
    stream << "Read registers V0 through V" << std::hex << static_cast<std::uint16_t>(x) << "from memory starting at location I.";
    return stream.str();
}

std::string OpcodeFx65::getMnemonic(void)
{
    std::stringstream stream;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", [I]";
    return stream.str();
}
