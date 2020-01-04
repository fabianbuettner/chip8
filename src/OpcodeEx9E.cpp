#include "OpcodeEx9E.h"

#include <iomanip>
#include <sstream>

OpcodeEx9E::OpcodeEx9E(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeEx9E::execute(void) {
    if(cpu.keypad[cpu.V[x]])
        cpu.PC += 2;

    return true;
}

std::string OpcodeEx9E::getDescription(void) {
    std::stringstream stream;
    stream << "Skip next instruction if key with the value of V" << std::hex << static_cast<std::uint16_t>(x) << " is pressed.";
    return stream.str();
}

std::string OpcodeEx9E::getMnemonic(void) {
    std::stringstream stream;
    stream << "SKP V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
