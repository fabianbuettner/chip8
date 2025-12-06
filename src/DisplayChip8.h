#pragma once

#include "Display.h"

#include <array>
#include <cstdint>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

const std::uint8_t width = 64;
const std::uint8_t height = 32;

class DisplayChip8 : public Display {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

public:
    std::array<std::uint32_t, height * width> memory = { 0 };

public:
    DisplayChip8(const std::string& name, float scale);
    ~DisplayChip8(void);
    void refresh(void) final;
};
