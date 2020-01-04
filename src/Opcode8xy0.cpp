#include "Opcode8xy0.h"

#include <iomanip>
#include <sstream>

Opcode8xy0::Opcode8xy0(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy0::execute(void) {
    cpu.V[x] = cpu.V[y];
    return true;
}

std::string Opcode8xy0::getDescription(void) {
    std::stringstream stream;
    stream << "Stores the value of register Vy in register Vx.";
    return stream.str();
}

std::string Opcode8xy0::getMnemonic(void) {
    std::stringstream stream;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
