#include "OpcodeFx55.h"

#include <iomanip>
#include <sstream>

OpcodeFx55::OpcodeFx55(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeFx55::execute(void)
{
    std::uint16_t x = (opcode & 0x0f00) >> 8;
    for (std::uint8_t i = 0; i <= x; i++) {
        cpu.memory[cpu.i + i] = cpu.v[i];
    }
    cpu.i += x + 1;
    return true;
}

std::string OpcodeFx55::getDescription(void)
{
    std::stringstream stream;
    stream << "The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.";
    return stream.str();
}

std::string OpcodeFx55::getMnemonic(void)
{
    std::stringstream stream;
    std::uint16_t x = (opcode & 0x0f00) >> 8;
    stream << "LD [I], V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
