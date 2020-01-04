#include "Emulator.h"

#include <boost/bind.hpp>

Emulator::Emulator(const std::string& name, boost::asio::io_service& io, Cpu& cpu)
    : cpu { cpu }
    , cpu_clock(io, boost::posix_time::milliseconds(1000 / cpu.clock_speed))
{
    SDL_Init(SDL_INIT_VIDEO);
    std::uint8_t scale = 10;
    std::uint8_t width = 64;
    std::uint8_t height = 32;
    window = SDL_CreateWindow(name.c_str(), 0, 0, width * scale, height * scale, SDL_WINDOW_SHOWN);
    // TODO, fab: check return value
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // TODO, fab: check return value
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // TODO, fab: check return value
    cpu_clock.async_wait(boost::bind(&Emulator::cycle, this));
}

Emulator::~Emulator(void)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Emulator::cycle(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return;
            case SDLK_x:
                cpu.keypad[0] = 1;
                break;
            case SDLK_1:
                cpu.keypad[1] = 1;
                break;
            case SDLK_2:
                cpu.keypad[2] = 1;
                break;
            case SDLK_3:
                cpu.keypad[3] = 1;
                break;
            case SDLK_q:
                cpu.keypad[4] = 1;
                break;
            case SDLK_w:
                cpu.keypad[5] = 1;
                break;
            case SDLK_e:
                cpu.keypad[6] = 1;
                break;
            case SDLK_a:
                cpu.keypad[7] = 1;
                break;
            case SDLK_s:
                cpu.keypad[8] = 1;
                break;
            case SDLK_d:
                cpu.keypad[9] = 1;
                break;
            case SDLK_y:
                cpu.keypad[10] = 1;
                break;
            case SDLK_c:
                cpu.keypad[11] = 1;
                break;
            case SDLK_4:
                cpu.keypad[12] = 1;
                break;
            case SDLK_r:
                cpu.keypad[13] = 1;
                break;
            case SDLK_f:
                cpu.keypad[14] = 1;
                break;
            case SDLK_v:
                cpu.keypad[15] = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_x:
                cpu.keypad[0] = 0;
                break;
            case SDLK_1:
                cpu.keypad[1] = 0;
                break;
            case SDLK_2:
                cpu.keypad[2] = 0;
                break;
            case SDLK_3:
                cpu.keypad[3] = 0;
                break;
            case SDLK_q:
                cpu.keypad[4] = 0;
                break;
            case SDLK_w:
                cpu.keypad[5] = 0;
                break;
            case SDLK_e:
                cpu.keypad[6] = 0;
                break;
            case SDLK_a:
                cpu.keypad[7] = 0;
                break;
            case SDLK_s:
                cpu.keypad[8] = 0;
                break;
            case SDLK_d:
                cpu.keypad[9] = 0;
                break;
            case SDLK_y:
                cpu.keypad[10] = 0;
                break;
            case SDLK_c:
                cpu.keypad[11] = 0;
                break;
            case SDLK_4:
                cpu.keypad[12] = 0;
                break;
            case SDLK_r:
                cpu.keypad[13] = 0;
                break;
            case SDLK_f:
                cpu.keypad[14] = 0;
                break;
            case SDLK_v:
                cpu.keypad[15] = 0;
                break;
            }
            break;
        }
    }
    if (!cpu.cycle()) {
        return;
    }
    SDL_UpdateTexture(texture, nullptr, &cpu.display[0], sizeof(cpu.display[0]) * 64);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    cpu_clock.expires_at(cpu_clock.expires_at() + boost::posix_time::milliseconds(1000 / cpu.clock_speed));
    cpu_clock.async_wait(boost::bind(&Emulator::cycle, this));
}
