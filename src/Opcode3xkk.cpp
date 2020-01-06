#include "Opcode3xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode3xkk::Opcode3xkk(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode3xkk::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    if (cpu.v[x] == kk) {
        cpu.pc += 2;
    }
    return true;
}

std::string Opcode3xkk::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    stream << "Skip next instruction if V" << std::hex << static_cast<std::uint16_t>(x) << " = " << int_to_hexstring(kk, 2) << ".";
    return stream.str();
}

std::string Opcode3xkk::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    stream << "SE V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
