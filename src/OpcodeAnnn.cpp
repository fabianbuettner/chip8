#include "OpcodeAnnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeAnnn::OpcodeAnnn(Cpu& cpu) : cpu{cpu} {
    nnn = cpu.opcode & 0x0fff;
}

bool OpcodeAnnn::execute(void) {
    cpu.I = nnn;
    return true;
}

std::string OpcodeAnnn::getDescription(void) {
    std::stringstream stream;
    stream << "The value of register I is set to " << int_to_hexstring(nnn, 3);
    return stream.str();
}

std::string OpcodeAnnn::getMnemonic(void) {
    std::stringstream stream;
    stream << "LD I, " << int_to_hexstring(nnn, 3);
    return stream.str();
}
