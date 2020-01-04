#include "OpcodeFx29.h"

#include <iomanip>
#include <sstream>

OpcodeFx29::OpcodeFx29(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx29::execute(void) {
    cpu.I = sprite_address + cpu.V[x] * 5;
    return true;
}

std::string OpcodeFx29::getDescription(void) {
    std::stringstream stream;
    stream << "Set I = location of sprite for digit V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx29::getMnemonic(void) {
    std::stringstream stream;
    stream << "LD F, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
