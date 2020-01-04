#include "OpcodeExA1.h"

#include <iomanip>
#include <sstream>

OpcodeExA1::OpcodeExA1(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeExA1::execute(void) {
    if(!cpu.keypad[cpu.V[x]])
        cpu.PC += 2;
        
    return true;
}

std::string OpcodeExA1::getDescription(void) {
    std::stringstream stream;
    stream << "Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.";
    return stream.str();
}

std::string OpcodeExA1::getMnemonic(void) {
    std::stringstream stream;
    stream << "SKNP V" << std::hex << static_cast<std::uint16_t>(x);
    return stream.str();
}
