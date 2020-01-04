#include "Opcode5xy0.h"

#include <iomanip>
#include <sstream>

Opcode5xy0::Opcode5xy0(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
}

bool Opcode5xy0::execute(void) {
    if(cpu.V[x] == cpu.V[y]) {
        cpu.PC += 2;
    }
    return true;
}

std::string Opcode5xy0::getDescription(void) {
    std::stringstream stream;
    stream << "Skip next instruction if V" << std::hex << static_cast<std::uint16_t>(x) << " = V" << static_cast<std::uint16_t>(y) << ".";
    return stream.str();
}

std::string Opcode5xy0::getMnemonic(void) {
    std::stringstream stream;
    stream << "SE V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y);
    return stream.str();
}
