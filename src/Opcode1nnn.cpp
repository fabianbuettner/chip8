#include "Opcode1nnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode1nnn::Opcode1nnn(Cpu& cpu)
    : cpu { cpu }
{
    nnn = cpu.opcode & 0x0fff;
}

bool Opcode1nnn::execute(void)
{
    cpu.PC = nnn;
    return true;
}

std::string Opcode1nnn::getDescription(void)
{
    std::stringstream stream;
    stream << "The interpreter sets the program counter to " << int_to_hexstring(nnn, 3) << ".";
    return stream.str();
}

std::string Opcode1nnn::getMnemonic(void)
{
    std::stringstream stream;
    stream << "JP " << int_to_hexstring(nnn, 3);
    return stream.str();
}
