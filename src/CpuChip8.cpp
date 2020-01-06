#include "CpuChip8.h"
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
#include "utilities.h"

#include <cstdlib>

CpuChip8::CpuChip8(MemoryChip8& memory, DisplayChip8& display, InputChip8& input, std::uint32_t clock_speed, std::uint16_t pc) : memory{ memory},
    display{ display },
    input{ input},
    pc{ pc } {
    srand(time(NULL));
    opcodes[0x00E0] = std::make_unique<Opcode00E0>(*this);
    opcodes[0x00EE] = std::make_unique<Opcode00EE>(*this);
    opcodes[0x1000] = std::make_unique<Opcode1nnn>(*this);
    opcodes[0x2000] = std::make_unique<Opcode2nnn>(*this);
    opcodes[0x3000] = std::make_unique<Opcode3xkk>(*this);
    opcodes[0x4000] = std::make_unique<Opcode4xkk>(*this);
    opcodes[0x5000] = std::make_unique<Opcode5xy0>(*this);
    opcodes[0x6000] = std::make_unique<Opcode6xkk>(*this);
    opcodes[0x7000] = std::make_unique<Opcode7xkk>(*this);
    opcodes[0x8000] = std::make_unique<Opcode8xy0>(*this);
    opcodes[0x8001] = std::make_unique<Opcode8xy1>(*this);
    opcodes[0x8002] = std::make_unique<Opcode8xy2>(*this);
    opcodes[0x8003] = std::make_unique<Opcode8xy3>(*this);
    opcodes[0x8004] = std::make_unique<Opcode8xy4>(*this);
    opcodes[0x8005] = std::make_unique<Opcode8xy5>(*this);
    opcodes[0x8006] = std::make_unique<Opcode8xy6>(*this);
    opcodes[0x8007] = std::make_unique<Opcode8xy7>(*this);
    opcodes[0x800e] = std::make_unique<Opcode8xyE>(*this);
    opcodes[0x9000] = std::make_unique<Opcode9xy0>(*this);
    opcodes[0xA000] = std::make_unique<OpcodeAnnn>(*this);
    opcodes[0xB000] = std::make_unique<OpcodeBnnn>(*this);
    opcodes[0xC000] = std::make_unique<OpcodeCxkk>(*this);
    opcodes[0xD000] = std::make_unique<OpcodeDxyn>(*this);
    opcodes[0xE09E] = std::make_unique<OpcodeEx9E>(*this);
    opcodes[0xE0A1] = std::make_unique<OpcodeExA1>(*this);
    opcodes[0xF007] = std::make_unique<OpcodeFx07>(*this);
    opcodes[0xF00A] = std::make_unique<OpcodeFx0A>(*this);
    opcodes[0xF015] = std::make_unique<OpcodeFx15>(*this);
    opcodes[0xF018] = std::make_unique<OpcodeFx18>(*this);
    opcodes[0xF01E] = std::make_unique<OpcodeFx1E>(*this);
    opcodes[0xF029] = std::make_unique<OpcodeFx29>(*this);
    opcodes[0xF033] = std::make_unique<OpcodeFx33>(*this);
    opcodes[0xF055] = std::make_unique<OpcodeFx55>(*this);
    opcodes[0xF065] = std::make_unique<OpcodeFx65>(*this);
    cycles_per_timer_tick = clock_speed / 60; // clock_speed Hz / 60 Hz
}

std::unique_ptr<Opcode> &CpuChip8::emitOpcode(std::uint8_t* pc)
{
    opcode = (pc[0] << 8) | pc[1];
    uint8_t opcode_key = pc[0] >> 4;
    std::uint16_t mask = 0xf000;
    if(opcode_key == 8) {
        mask = 0xf00f;
    }
    else if(opcode_key == 0x00 || opcode_key == 0x0e || opcode_key == 0x0f) {
        mask = 0xf0ff;
    }

    std::unique_ptr<Opcode>& o = opcodes[opcode & mask];
    if(o) {
        o->setOpcode(opcode);
    }
    return o;
}

void CpuChip8::setVerbosity(bool new_verbosity)
{
    verbosity = new_verbosity;
}

bool CpuChip8::cycle(void) {
    bool rc = false;
    static std::uint32_t cycle_counter = 1;
    std::unique_ptr<Opcode>& instruction = emitOpcode(&memory[pc]);
    if (!instruction) {
        std::cout << "Not an opcode?";
        return false;
    }

    if (verbosity)
        std::cout << int_to_hexstring(pc, 4) << "\t";

    pc += 2;
    if (!instruction->execute())
        return false;

    if (verbosity)
        std::cout << int_to_hexstring(opcode, 4) << "\t" << instruction->getMnemonic() << std::endl;


    if (cycle_counter >= cycles_per_timer_tick) {
        if (delay_timer) {
            --delay_timer;
        }
        if (sound_timer) {
            --sound_timer;
        }
        cycle_counter = 1;
    }

    rc = input.cycle();
    if(!rc)
        return rc;

    cycle_counter++;

    return true;
}

std::ostream& CpuChip8::write(std::ostream& os) const
{
    os << "Cpu state" << std::endl;
    os << "name" << "\t" << "value" << std::endl;
    os << "i" << "\t" << int_to_hexstring(i, 3) << std::endl;
    os << "op" << "\t" << int_to_hexstring(opcode, 4) << std::endl;
    os << "pc" << "\t" << int_to_hexstring(pc, 3) << std::endl;
    os << "sp" << "\t" << int_to_hexstring(sp, 2) << std::endl;
    std::uint8_t index = 0;
    for (auto i : v) {
        os << "v" << std::hex << static_cast<std::uint16_t>(index++) << "\t" << int_to_hexstring(i, 2) << "\t" << std::endl;
    }
    return os;
}

std::ostream& CpuChip8::printDisassembly(std::ostream& os) {
    os << "address\topcode\tdescription" << std::endl;
    for (std::uint32_t i = pc; i < memory.size();) {
        std::unique_ptr<Opcode>& instruction = emitOpcode(&memory[i]);
        if (instruction) {
            os << int_to_hexstring(i, 3) << "\t" << int_to_hexstring(opcode, 4) << "\t" << instruction->getMnemonic() << std::endl;
            i += 2;
        } else {
            os << int_to_hexstring(i, 3) << "\t" << int_to_hexstring(memory[i], 2) << "\t"
               << "not an opcode" << std::endl;
            i++;
        }
    }

    return os;
}
