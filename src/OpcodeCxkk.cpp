#include "OpcodeCxkk.h"
#include "utilities.h"

#include <iomanip>
#include <sstream>

OpcodeCxkk::OpcodeCxkk(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeCxkk::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    std::uint8_t random_byte = rand();
    cpu.v[x] = random_byte & kk;
    return true;
}

std::string OpcodeCxkk::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    stream << "Set V" << std::hex << static_cast<std::uint16_t>(x) << " = random byte AND " << int_to_hexstring(kk, 2) << ".";
    return stream.str();
}

std::string OpcodeCxkk::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t kk = opcode & 0xff;
    stream << "RND V" << std::hex << static_cast<std::uint16_t>(x) << ", random byte AND " << int_to_hexstring(kk, 2);
    return stream.str();
}
