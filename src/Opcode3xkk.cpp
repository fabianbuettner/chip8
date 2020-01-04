#include "Opcode3xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode3xkk::Opcode3xkk(Cpu& cpu)
    : cpu { cpu }
{
    x = (cpu.opcode & 0x0f00) >> 8;
    kk = cpu.opcode & 0xff;
}

bool Opcode3xkk::execute(void)
{
    if (cpu.V[x] == kk) {
        cpu.PC += 2;
    }
    return true;
}

std::string Opcode3xkk::getDescription(void)
{
    std::stringstream stream;
    stream << "Skip next instruction if V" << std::hex << static_cast<std::uint16_t>(x) << " = " << int_to_hexstring(kk, 2) << ".";
    return stream.str();
}

std::string Opcode3xkk::getMnemonic(void)
{
    std::stringstream stream;
    stream << "SE V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
