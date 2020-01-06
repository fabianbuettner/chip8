#include "DisplayChip8.h"

DisplayChip8::DisplayChip8(const std::string& name, float scale)
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(name.c_str(), 0, 0, width * scale, height * scale, SDL_WINDOW_SHOWN);
    // TODO, fab: check return value
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // TODO, fab: check return value
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    // TODO, fab: check return value
}

DisplayChip8::~DisplayChip8(void)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void DisplayChip8::refresh(void)
{
    SDL_UpdateTexture(texture, nullptr, &memory[0], sizeof(memory[0]) * width);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    return;
}
