#include "Opcode9xy0.h"

#include <iomanip>
#include <sstream>

Opcode9xy0::Opcode9xy0(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode9xy0::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    if (cpu.v[x] != cpu.v[y]) {
        cpu.pc += 2;
    }
    return true;
}

std::string Opcode9xy0::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "Skip next instruction if V" << std::hex << static_cast<std::uint16_t>(x) << " != V" << static_cast<std::uint16_t>(y) << ".";
    return stream.str();
}

std::string Opcode9xy0::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    stream << "SNE V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
