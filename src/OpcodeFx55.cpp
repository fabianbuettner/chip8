#include "OpcodeFx55.h"

#include <iomanip>
#include <sstream>

OpcodeFx55::OpcodeFx55(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx55::execute(void)
{
    for (std::uint8_t i = 0; i <= x; i++) {
        cpu.program[cpu.I + i] = cpu.V[i];
    }
    cpu.I += x + 1;
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
    stream << "LD [I], V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
