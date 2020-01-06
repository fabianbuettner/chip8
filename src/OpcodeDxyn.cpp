#include "OpcodeDxyn.h"
#include "utilities.h"

#include <climits>
#include <iomanip>
#include <sstream>

OpcodeDxyn::OpcodeDxyn(CpuChip8& cpu)
    : cpu { cpu }
{
}

bool OpcodeDxyn::execute(void)
{
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    std::uint8_t n = opcode & 0xf;
    std::uint8_t column = cpu.v[x];
    std::uint8_t row = cpu.v[y];
    cpu.v[0xf] = 0;
    for (std::uint8_t i = 0; i < n; i++) {
        std::uint8_t sprite_pixels = cpu.memory[cpu.i + i];
        for (std::uint8_t j = 0; j < CHAR_BIT; j++) {
            std::uint8_t sprite_pixel = (sprite_pixels >> ((CHAR_BIT - 1) - j)) & 0x01;
            if (!sprite_pixel)
                continue;
            std::uint32_t* display_pixel = &cpu.display.memory[((row + i) % 32) * 64 + (column + j) % 64];
            if (*display_pixel == 0xffffffff) {
                cpu.v[0xf] = 1;
            }
            *display_pixel ^= 0xffffffff;
        }
    }
    cpu.display.refresh();
    return true;
}

std::string OpcodeDxyn::getDescription(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    std::uint8_t n = opcode & 0xf;
    stream << "Display " << int_to_hexstring(n, 1) << "-byte sprite starting at memory location I at (V" << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y) << "), set VF = collision.";
    return stream.str();
}

std::string OpcodeDxyn::getMnemonic(void)
{
    std::stringstream stream;
    std::uint8_t x = (opcode & 0x0f00) >> 8;
    std::uint8_t y = (opcode & 0x00f0) >> 4;
    std::uint8_t n = opcode & 0xf;
    stream << "DRW V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y) << ", " << int_to_hexstring(n, 1);
    return stream.str();
}
