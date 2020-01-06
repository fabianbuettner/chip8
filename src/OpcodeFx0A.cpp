#include "OpcodeFx0A.h"

#include <iomanip>
#include <sstream>

OpcodeFx0A::OpcodeFx0A(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx0A::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    for (std::uint8_t i = 0; i < 16; i++) {
        if (cpu.input.keypad[i]) {
            cpu.v[x] = i;
            return true;
        }
    }
    cpu.pc -= 2;
    return true;
}

std::string OpcodeFx0A::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Wait for a key press, store the value of the key in V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx0A::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", K";
    return stream.str();
}
