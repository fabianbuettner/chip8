#include "OpcodeFx18.h"

#include <iomanip>
#include <sstream>

OpcodeFx18::OpcodeFx18(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx18::execute(void) {
    cpu.sound_timer = cpu.V[0];
    return true;
}

std::string OpcodeFx18::getDescription(void) {
    std::stringstream stream;
    stream << "Set sound timer = V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx18::getMnemonic(void) {
    std::stringstream stream;
    stream << "LD ST, V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
