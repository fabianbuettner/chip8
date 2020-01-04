#include "Opcode00EE.h"

Opcode00EE::Opcode00EE(Cpu& cpu)
    : cpu { cpu }
{
}

std::string Opcode00EE::getDescription(void)
{
    return "The interpreter subtracts 1 from the stack pointer, then sets the program counter to the address at the top of the stack.";
}

bool Opcode00EE::execute(void)
{
    cpu.PC = cpu.stack[--cpu.SP];
    return true;
}

std::string Opcode00EE::getMnemonic(void)
{
    std::stringstream stream;
    stream << "RET";
    return stream.str();
}
