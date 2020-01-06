#include "MachineChip8.h"

#include <iostream>

MachineChip8::MachineChip8(Cpu& cpu, std::uint32_t emulation_clock_speed) : cpu{ cpu } {
}

bool MachineChip8::cycle(void) {
    if(!cpu.cycle())
        return false;
    return true;
}
