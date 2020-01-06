#pragma once

#include "Cpu.h"
#include "DisplayChip8.h"
#include "InputChip8.h"
#include "MemoryChip8.h"
#include "Opcode.h"

#include <array>
#include <cstdint>
#include <memory>
#include <map>

const std::uint16_t pc_start_address = 0x200;

class CpuChip8 : public Cpu {
private:
    bool verbosity = false;
    std::map<std::uint16_t, std::unique_ptr<Opcode>> opcodes;
public:
    MemoryChip8& memory;
    DisplayChip8& display;
    InputChip8& input;
    std::uint16_t i = 0;
    std::uint16_t opcode = 0x0000;
    std::uint16_t pc;
    std::uint16_t sp = 0;
    std::array<std::uint16_t, 16> stack;
    std::array<std::uint8_t, 16> v = { 0 };
    std::uint8_t sound_timer = 0;
    std::uint8_t delay_timer = 0;
    std::uint32_t cycles_per_timer_tick;
public:
    CpuChip8(MemoryChip8& memory, DisplayChip8& display, InputChip8& input, std::uint32_t clock_speed = 0, std::uint16_t pc = pc_start_address);
    std::unique_ptr<Opcode> &emitOpcode(std::uint8_t* pc);
    void setVerbosity(bool verbosity);

    bool cycle(void) final;
    std::ostream& printDisassembly(std::ostream &os) final ;
    std::ostream& write(std::ostream& os) const final;
};
