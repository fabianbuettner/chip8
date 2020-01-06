#pragma once

#include "Cpu.h"
#include "Machine.h"

#include <cstdint>

struct MachineChip8 : public Machine {
    Cpu& cpu;

public:
    MachineChip8(Cpu& cpu, std::uint32_t emulation_clock_speed);

    bool cycle(void) final;
};
