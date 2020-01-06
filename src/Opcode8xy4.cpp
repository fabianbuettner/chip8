#include "Opcode8xy4.h"

#include <iomanip>
#include <sstream>

Opcode8xy4::Opcode8xy4(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode8xy4::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    cpu.v[0xf] = (cpu.v[x] > 0xff - cpu.v[y]);
    cpu.v[x] += cpu.v[y];
    return true;
}

std::string Opcode8xy4::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "The values of V" << static_cast<std::uint16_t>(x) << " and V" << static_cast<std::uint16_t>(y) << " are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in V" << static_cast<std::uint16_t>(x);
    return stream.str();
}

std::string Opcode8xy4::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "ADD V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
