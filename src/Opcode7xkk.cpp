#include "Opcode7xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode7xkk::Opcode7xkk(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode7xkk::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = opcode & 0xff;
    cpu.v[x] += kk;
    return true;
}

std::string Opcode7xkk::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = opcode & 0xff;
    stream << "Adds the value " << int_to_hexstring(kk, 2) << " to the value of register V" << static_cast<std::uint16_t>(x) << ", then stores the result in Vx.";
    return stream.str();
}

std::string Opcode7xkk::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint16_t kk = opcode & 0xff;
    stream << "ADD V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
