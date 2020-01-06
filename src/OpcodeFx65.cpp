#include "OpcodeFx65.h"

#include <iomanip>
#include <sstream>

OpcodeFx65::OpcodeFx65(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx65::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    for (std::uint8_t i = 0; i <= x; i++) {
        cpu.v[i] = cpu.memory[cpu.i + i];
    }
    cpu.i += x + 1;
    return true;
}

std::string OpcodeFx65::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Read registers V0 through V" << std::hex << static_cast<std::uint16_t>(x) << "from memory starting at location I.";
    return stream.str();
}

std::string OpcodeFx65::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", [I]";
    return stream.str();
}
