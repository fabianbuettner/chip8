#include "Opcode1nnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode1nnn::Opcode1nnn(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode1nnn::execute(void)
{
    std::uint16_t nnn = opcode & 0x0fff;
    cpu.pc = nnn;
    return true;
}

std::string Opcode1nnn::getDescription(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "The interpreter sets the program counter to " << int_to_hexstring(nnn, 3) << ".";
    return stream.str();
}

std::string Opcode1nnn::getMnemonic(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "JP " << int_to_hexstring(nnn, 3);
    return stream.str();
}
