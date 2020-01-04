#include "OpcodeDxyn.h"
#include "utilities.h"

#include <climits>
#include <iomanip>
#include <sstream>

OpcodeDxyn::OpcodeDxyn(Cpu& cpu) : cpu{cpu} {
    x = (cpu.opcode & 0x0f00) >> 8;
    y = (cpu.opcode & 0x00f0) >> 4;
    n = cpu.opcode & 0xf;
}

bool OpcodeDxyn::execute(void) {
    std::uint8_t column = cpu.V[x];
    std::uint8_t row = cpu.V[y];
    cpu.V[0xf] = 0;
    for(std::uint8_t i = 0; i < n; i++) {
        std::uint8_t sprite_pixels = cpu.program[cpu.I + i];
        for(std::uint8_t j = 0; j < CHAR_BIT; j++) {
            std::uint8_t sprite_pixel = (sprite_pixels >> ((CHAR_BIT - 1) - j)) & 0x01;
            if(!sprite_pixel)
                continue;
            std::uint32_t* display_pixel = &cpu.display[((row + i) % 32) * 64 + (column + j) % 64];
            if(*display_pixel == 0xffffffff) {
                cpu.V[0xf] = 1;
            }
            *display_pixel ^= 0xffffffff;
        }
    }
    return true;
}

std::string OpcodeDxyn::getDescription(void) {
    std::stringstream stream;
    stream << "Display " << int_to_hexstring(n, 1)<< "-byte sprite starting at memory location I at (V" << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y) << "), set VF = collision.";
    return stream.str();
}

std::string OpcodeDxyn::getMnemonic(void) {
    std::stringstream stream;
    stream << "DRW V" << std::hex << static_cast<std::uint16_t>(x) << ", V" << static_cast<std::uint16_t>(y) << ", " << int_to_hexstring(n, 1);
    return stream.str();
}
