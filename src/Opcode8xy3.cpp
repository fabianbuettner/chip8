#include "Opcode8xy3.h"

#include <iomanip>
#include <sstream>

Opcode8xy3::Opcode8xy3(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy3::execute(void) {
    cpu.V[x] ^= cpu.V[y];
    return true;
}

std::string Opcode8xy3::getDescription(void) {
    std::stringstream stream;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(x) << " ^ V" << static_cast<std::uint16_t>(y) << ".";
    return stream.str();
}

std::string Opcode8xy3::getMnemonic(void) {
    std::stringstream stream;
    stream << "XOR V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
