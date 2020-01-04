#include "OpcodeCxkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeCxkk::OpcodeCxkk(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    kk = cpu.opcode & 0xff;
    random_byte = rand();
}

bool OpcodeCxkk::execute(void) {
    cpu.V[x] = random_byte & kk;
    return true;
}

std::string OpcodeCxkk::getDescription(void) {
    std::stringstream stream;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = " << int_to_hexstring(random_byte, 2) << " AND " << int_to_hexstring(kk, 2) << ".";
    return stream.str();
}

std::string OpcodeCxkk::getMnemonic(void) {
    std::stringstream stream;
    stream << "RND V" << std::hex << static_cast<std::uint16_t>(x) << ", " << int_to_hexstring(random_byte, 2);
    return stream.str();
}
