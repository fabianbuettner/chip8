#include "Opcode00EE.h"

#include <sstream>

Opcode00EE::Opcode00EE(CpuChip8& cpu)
    : cpu { cpu }
{
}

std::string Opcode00EE::getDescription(void)
{
    return "The interpreter subtracts 1 from the stack pointer, then sets the program counter to the address at the top of the stack.";
}

bool Opcode00EE::execute(void)
{
    cpu.pc = cpu.stack[--cpu.sp];
    return true;
}

std::string Opcode00EE::getMnemonic(void)
{
    std::stringstream stream;
    stream << "RET";
    return stream.str();
}
