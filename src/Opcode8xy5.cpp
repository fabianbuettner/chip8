#include "Opcode8xy5.h"

#include <iomanip>
#include <sstream>

Opcode8xy5::Opcode8xy5(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode8xy5::execute(void) {
    cpu.V[0xf] = cpu.V[x] > cpu.V[y];
    cpu.V[x] -= cpu.V[y];
    return true;
}

std::string Opcode8xy5::getDescription(void) {
    std::stringstream stream;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(x) << " - V" << static_cast<std::uint16_t>(y) << ", set VF = NOT borrow";
    return stream.str();
}

std::string Opcode8xy5::getMnemonic(void) {
    std::stringstream stream;
    stream << "SUB V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
