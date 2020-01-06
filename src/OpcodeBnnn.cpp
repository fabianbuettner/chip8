#include "OpcodeBnnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeBnnn::OpcodeBnnn(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeBnnn::execute(void)
{
    std::uint16_t nnn = opcode & 0x0fff;
    cpu.pc = nnn + cpu.v[0];
    return true;
}

std::string OpcodeBnnn::getDescription(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "The program counter is set to " << int_to_hexstring(nnn, 3) << " plus the value of V0";
    return stream.str();
}

std::string OpcodeBnnn::getMnemonic(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "JP V0, " << int_to_hexstring(nnn, 3);
    return stream.str();
}
