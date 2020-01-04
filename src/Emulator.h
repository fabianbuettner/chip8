#pragma once

#include "Cpu.h"

#include <SDL2/SDL.h>
#include <boost/asio.hpp>

class Emulator {
private:
    Cpu& cpu;
    boost::asio::deadline_timer cpu_clock;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

public:
    Emulator(const std::string& name, boost::asio::io_service& io, Cpu& cpu);
    ~Emulator(void);

private:
    void cycle(void);
};
