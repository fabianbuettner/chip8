#include "Opcode4xkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode4xkk::Opcode4xkk(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    kk = cpu.opcode & 0xff;
}

bool Opcode4xkk::execute(void) {
    if(cpu.V[x] != kk) {
        cpu.PC += 2;
    }
    return true;
}

std::string Opcode4xkk::getDescription(void) {
    std::stringstream stream;
    stream << "Skip next instruction if V" << std::hex << static_cast<std::uint16_t>(x) << " != " << int_to_hexstring(kk, 2) << ".";
    return stream.str();
}

std::string Opcode4xkk::getMnemonic(void) {
    std::stringstream stream;
    stream << "SNE V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(kk, 2);
    return stream.str();
}
