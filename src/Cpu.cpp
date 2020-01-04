#include "Cpu.h"
#include "Opcode00E0.h"
#include "Opcode00EE.h"
#include "Opcode1nnn.h"
#include "Opcode2nnn.h"
#include "Opcode3xkk.h"
#include "Opcode4xkk.h"
#include "Opcode5xy0.h"
#include "Opcode6xkk.h"
#include "Opcode7xkk.h"
#include "Opcode8xy0.h"
#include "Opcode8xy1.h"
#include "Opcode8xy2.h"
#include "Opcode8xy3.h"
#include "Opcode8xy4.h"
#include "Opcode8xy5.h"
#include "Opcode8xy6.h"
#include "Opcode8xy7.h"
#include "Opcode8xyE.h"
#include "Opcode9xy0.h"
#include "OpcodeAnnn.h"
#include "OpcodeBnnn.h"
#include "OpcodeCxkk.h"
#include "OpcodeDxyn.h"
#include "OpcodeEx9E.h"
#include "OpcodeExA1.h"
#include "OpcodeFx07.h"
#include "OpcodeFx0A.h"
#include "OpcodeFx15.h"
#include "OpcodeFx18.h"
#include "OpcodeFx1E.h"
#include "OpcodeFx29.h"
#include "OpcodeFx33.h"
#include "OpcodeFx55.h"
#include "OpcodeFx65.h"
//#include "ExecuteMachineLanguageSubroutineInstruction.h"
//#include "IllegalInstruction.h"
#include "utilities.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iterator>

const std::array<const std::uint8_t, 16 * 5> sprites = {
    0xf0, 0x90, 0x90, 0x90, 0xf0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xf0, 0x10, 0xf0, 0x80, 0xf0, // 2
    0xf0, 0x10, 0xf0, 0x10, 0xf0, // 3
    0x90, 0x90, 0xf0, 0x10, 0x10, // 4
    0xf0, 0x80, 0xf0, 0x10, 0xf0, // 5
    0xf0, 0x80, 0xf0, 0x90, 0xf0, // 6
    0xf0, 0x10, 0x20, 0x40, 0x40, // 7
    0xf0, 0x90, 0xf0, 0x90, 0xf0, // 8
    0xf0, 0x90, 0xf0, 0x10, 0xf0, // 9
    0xf0, 0x90, 0xf0, 0x90, 0x90, // a
    0xe0, 0x90, 0xe0, 0x90, 0xe0, // b
    0xf0, 0x80, 0x80, 0x80, 0xf0, // c
    0xe0, 0x90, 0x90, 0x90, 0xe0, // d
    0xf0, 0x80, 0xf0, 0x80, 0xf0, // e
    0xf0, 0x80, 0xf0, 0x80, 0x80 // f
};

Cpu::Cpu(const std::filesystem::path& path, std::uint32_t clock_speed)
    : clock_speed { clock_speed }
{
    // INFO, fab: Only support 1 - 1000 Hz, as Emulator.cpp assumes that range...
    assert(clock_speed <= 1000);

    if (!std::filesystem::is_regular_file(path)) {
        throw std::invalid_argument("Could not open input file!");
    }

    if (std::filesystem::file_size(path) > max_program_memory_size) {
        throw std::invalid_argument("Program too large!");
    }

    // Reserve memory for program + interpreter
    program.resize(std::filesystem::file_size(path) + pc_start_address, 0);

    // Load sprites into memory
    std::copy(sprites.begin(), sprites.end(), program.begin() + sprite_address);

    std::ifstream in { path, std::ios_base::binary };
    in.read(reinterpret_cast<char*>(&program[pc_start_address]), std::filesystem::file_size(path));

    srand(time(NULL));
}

Cpu::~Cpu()
{
}

std::shared_ptr<Opcode> Cpu::emitInstruction(std::uint8_t* pc)
{
    opcode = (pc[0] << 8) | pc[1];
    uint8_t key = pc[0] >> 4;
    uint16_t param = ((pc[0] & 0xf) << 8) | pc[1];
    switch (key) {
    case 0x0:
        switch (param) {
        case 0xe0:
            return std::make_shared<Opcode00E0>(*this);
        case 0xee:
            return std::make_shared<Opcode00EE>(*this);
        default:
            return nullptr;
        }
    case 0x1:
        return std::make_shared<Opcode1nnn>(*this);
    case 0x2:
        return std::make_shared<Opcode2nnn>(*this);
    case 0x3:
        return std::make_shared<Opcode3xkk>(*this);
    case 0x4:
        return std::make_shared<Opcode4xkk>(*this);
    case 0x5:
        return std::make_shared<Opcode5xy0>(*this);
    case 0x6:
        return std::make_shared<Opcode6xkk>(*this);
    case 0x7:
        return std::make_shared<Opcode7xkk>(*this);
    case 0x8:
        switch (param & 0xf) {
        case 0x0:
            return std::make_shared<Opcode8xy0>(*this);
        case 0x1:
            return std::make_shared<Opcode8xy1>(*this);
        case 0x2:
            return std::make_shared<Opcode8xy2>(*this);
        case 0x3:
            return std::make_shared<Opcode8xy3>(*this);
        case 0x4:
            return std::make_shared<Opcode8xy4>(*this);
        case 0x5:
            return std::make_shared<Opcode8xy5>(*this);
        case 0x6:
            return std::make_shared<Opcode8xy6>(*this);
        case 0x7:
            return std::make_shared<Opcode8xy7>(*this);
        case 0xe:
            return std::make_shared<Opcode8xyE>(*this);
        default:
            return nullptr;
        }
    case 0x9:
        switch (param & 0xf) {
        case 0x0:
            return std::make_shared<Opcode9xy0>(*this);
        default:
            return nullptr;
        }
    case 0xa:
        return std::make_shared<OpcodeAnnn>(*this);
    case 0xb:
        return std::make_shared<OpcodeBnnn>(*this);
    case 0xc:
        return std::make_shared<OpcodeCxkk>(*this);
    case 0xd:
        return std::make_shared<OpcodeDxyn>(*this);
    case 0xe:
        switch (param & 0xff) {
        case 0x9e:
            return std::make_shared<OpcodeEx9E>(*this);
        case 0xa1:
            return std::make_shared<OpcodeExA1>(*this);
        default:
            return nullptr;
        }
    case 0xf:
        switch (param & 0xff) {
        case 0x07:
            return std::make_shared<OpcodeFx07>(*this);
        case 0x0a:
            return std::make_shared<OpcodeFx0A>(*this);
        case 0x15:
            return std::make_shared<OpcodeFx15>(*this);
        case 0x18:
            return std::make_shared<OpcodeFx18>(*this);
        case 0x1e:
            return std::make_shared<OpcodeFx1E>(*this);
        case 0x29:
            return std::make_shared<OpcodeFx29>(*this);
        case 0x33:
            return std::make_shared<OpcodeFx33>(*this);
        case 0x55:
            return std::make_shared<OpcodeFx55>(*this);
        case 0x65:
            return std::make_shared<OpcodeFx65>(*this);
        default:
            return nullptr;
        }
    default:
        return nullptr;
    }
}

bool Cpu::cycle(void)
{
    std::shared_ptr<Opcode> instruction = emitInstruction(&program[PC]);
    if (!instruction) {
        return false;
    }

    if (verbosity)
        std::cout << int_to_hexstring(PC, 4) << "\t" << int_to_hexstring(opcode, 4) << "\t" << instruction->getMnemonic() << std::endl;

    PC += 2;
    if (!instruction->execute())
        return false;

    if (++update_timers >= (clock_speed / 60)) {
        if (delay_timer) {
            --delay_timer;
        }
        if (sound_timer) {
            --sound_timer;
        }
        update_timers = 0;
    }

    return true;
}

void Cpu::setVerbosity(bool new_verbosity)
{
    verbosity = new_verbosity;
}

std::ostream& operator<<(std::ostream& os, Cpu& cpu)
{
    std::uint8_t index = 0;
    os << "Cpu state" << std::endl;
    os << "name\tvalue" << std::endl;
    os << "PC\t0x" << int_to_hexstring(cpu.PC, 4) << std::endl;
    os << "I\t0x" << int_to_hexstring(cpu.I, 4) << std::endl;
    for (auto i : cpu.V) {
        os << "V" << std::to_string(index++) << "\t0x" << int_to_hexstring(static_cast<std::uint16_t>(i), 2) << "\t" << std::endl;
    }
    return os;
}
