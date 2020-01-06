#include "Opcode6xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode6xkk::Opcode6xkk(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode6xkk::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = (opcode & 0xff);
    cpu.v[x] = kk;
    return true;
}

std::string Opcode6xkk::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = (opcode & 0xff);
    stream << "The interpreter puts the value kk into register Vx.";
    return stream.str();
}

std::string Opcode6xkk::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = (opcode & 0xff);
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
