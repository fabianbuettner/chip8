#include "OpcodeEx9E.h"

#include <iomanip>
#include <sstream>

OpcodeEx9E::OpcodeEx9E(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeEx9E::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    if (cpu.input.keypad[cpu.v[x]])
        cpu.pc += 2;

    return true;
}

std::string OpcodeEx9E::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "Skip next instruction if key with the value of V" << std::hex << static_cast<std::uint16_t>(x) << " is pressed.";
    return stream.str();
}

std::string OpcodeEx9E::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    stream << "SKP V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
