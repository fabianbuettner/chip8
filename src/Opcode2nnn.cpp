#include "Opcode2nnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode2nnn::Opcode2nnn(Cpu& cpu)
    : cpu { cpu }
{
    nnn = cpu.opcode & 0x0fff;
}

bool Opcode2nnn::execute(void)
{
    cpu.stack[cpu.SP++] = cpu.PC;
    cpu.PC = nnn;
    return true;
}

std::string Opcode2nnn::getDescription(void)
{
    std::stringstream stream;
    stream << "The interpreter puts the current PC on the top of the stack, then increments the stack pointer. The PC is then set to " << int_to_hexstring(nnn, 3);
    return stream.str();
}

std::string Opcode2nnn::getMnemonic(void)
{
    std::stringstream stream;
    stream << "CALL " << int_to_hexstring(nnn, 3);
    return stream.str();
}
