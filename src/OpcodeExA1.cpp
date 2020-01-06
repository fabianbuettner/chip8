#include "OpcodeExA1.h"

#include <iomanip>
#include <sstream>

OpcodeExA1::OpcodeExA1(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeExA1::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    if (!cpu.input.keypad[cpu.v[x]])
        cpu.pc += 2;

    return true;
}

std::string OpcodeExA1::getDescription(void)
{
    std::stringstream stream;
    stream << "Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.";
    return stream.str();
}

std::string OpcodeExA1::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "SKNP V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
