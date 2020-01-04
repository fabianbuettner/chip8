#include "OpcodeFx0A.h"

#include <iomanip>
#include <sstream>

OpcodeFx0A::OpcodeFx0A(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
}

bool OpcodeFx0A::execute(void) {
    for(std::uint8_t i = 0; i < 16; i++) {
        if(cpu.keypad[i]) {
            cpu.V[x] = i;
            return true;
        }
    }
    cpu.PC -= 2;
    return true;
}

std::string OpcodeFx0A::getDescription(void) {
    std::stringstream stream;
    stream << "Wait for a key press, store the value of the key in V" << std::hex << static_cast<std::uint16_t>(x) << ".";
    return stream.str();
}

std::string OpcodeFx0A::getMnemonic(void) {
    std::stringstream stream;
    stream << "LD V" << std::hex << static_cast<std::uint16_t>(x) << ", K";
    return stream.str();
}
