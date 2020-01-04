#pragma once

#include "Opcode.h"

#include <array>
#include <filesystem>
#include <memory>

const std::uint16_t pc_start_address = 0x200;
const std::uint16_t max_program_memory_size = 0x1000 - pc_start_address;
// sprite_address is an arbitrary address
const std::uint16_t sprite_address = 0x010;

class Cpu {
public:
    std::uint16_t opcode = 0x0000;
    std::uint16_t PC = pc_start_address;
    std::uint16_t I = 0;
    std::array<std::uint8_t, 16> V = { 0 };
    std::uint8_t sound_timer = 0;
    std::uint8_t delay_timer = 0;
    std::vector<std::uint8_t> program;
    std::uint8_t SP = 0x0;
    std::array<std::uint16_t, 16> stack;
    std::array<std::uint32_t, 64 * 32> display = { 0 };
    std::array<std::uint8_t, 16> keypad = { 0 };
    std::uint32_t clock_speed;

private:
    bool verbosity = false;
    std::uint32_t update_timers = 0;

public:
    Cpu(const std::filesystem::path& path, std::uint32_t clock_speed);
    ~Cpu();
    std::shared_ptr<Opcode> emitInstruction(std::uint8_t* pc);
    bool cycle(void);
    void setVerbosity(bool verbosity);
    friend std::ostream& operator<<(std::ostream& os, Cpu& cpu);
};
