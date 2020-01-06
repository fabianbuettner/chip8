#pragma once

#include "Input.h"

#include <SDL2/SDL.h>
#include <array>

struct InputChip8 : public Input {
    std::array<std::uint16_t, 16> keypad;
    InputChip8(void);
    ~InputChip8(void);
    bool cycle(void) final;
};
