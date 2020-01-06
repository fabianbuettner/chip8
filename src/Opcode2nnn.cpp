#include "Opcode2nnn.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

Opcode2nnn::Opcode2nnn(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool Opcode2nnn::execute(void)
{
    std::uint16_t nnn = opcode & 0x0fff;
    cpu.stack[cpu.sp++] = cpu.pc;
    cpu.pc = nnn;
    return true;
}

std::string Opcode2nnn::getDescription(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "The interpreter puts the current PC on the top of the stack, then increments the stack pointer. The PC is then set to " << int_to_hexstring(nnn, 3);
    return stream.str();
}

std::string Opcode2nnn::getMnemonic(void)
{
    std::stringstream stream;
    std::uint16_t nnn = opcode & 0x0fff;
    stream << "CALL " << int_to_hexstring(nnn, 3);
    return stream.str();
}
