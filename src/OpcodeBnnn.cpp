#include "OpcodeBnnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeBnnn::OpcodeBnnn(Cpu& cpu) : cpu{cpu} {
    nnn = cpu.opcode & 0x0fff;
}

bool OpcodeBnnn::execute(void) {
    cpu.PC = nnn + cpu.V[0];
    return true;
}

std::string OpcodeBnnn::getDescription(void) {
    std::stringstream stream;
    stream << "The program counter is set to " << int_to_hexstring(nnn, 3) << " plus the value of V0";
    return stream.str();
}

std::string OpcodeBnnn::getMnemonic(void) {
    std::stringstream stream;
    stream << "JP V0, " << int_to_hexstring(nnn, 3);
    return stream.str();
}
