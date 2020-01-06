#include "OpcodeAnnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeAnnn::OpcodeAnnn(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeAnnn::execute(void)
{
    std::uint16_t nnn = opcode & 0x0fff;
    cpu.i = nnn;
    return true;
}

std::string OpcodeAnnn::getDescription(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "The value of register I is set to " << int_to_hexstring(nnn, 3);
    return stream.str();
}

std::string OpcodeAnnn::getMnemonic(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "LD I, " << int_to_hexstring(nnn, 3);
    return stream.str();
}
