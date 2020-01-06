#include "InputChip8.h"

InputChip8::InputChip8(void) {
    SDL_InitSubSystem(SDL_INIT_EVENTS);
}

InputChip8::~InputChip8(void) {
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

bool InputChip8::cycle(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return false;
            case SDLK_x:
                keypad[0] = 1;
                break;
            case SDLK_1:
                keypad[1] = 1;
                break;
            case SDLK_2:
                keypad[2] = 1;
                break;
            case SDLK_3:
                keypad[3] = 1;
                break;
            case SDLK_q:
                keypad[4] = 1;
                break;
            case SDLK_w:
                keypad[5] = 1;
                break;
            case SDLK_e:
                keypad[6] = 1;
                break;
            case SDLK_a:
                keypad[7] = 1;
                break;
            case SDLK_s:
                keypad[8] = 1;
                break;
            case SDLK_d:
                keypad[9] = 1;
                break;
            case SDLK_y:
                keypad[10] = 1;
                break;
            case SDLK_c:
                keypad[11] = 1;
                break;
            case SDLK_4:
                keypad[12] = 1;
                break;
            case SDLK_r:
                keypad[13] = 1;
                break;
            case SDLK_f:
                keypad[14] = 1;
                break;
            case SDLK_v:
                keypad[15] = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_x:
                keypad[0] = 0;
                break;
            case SDLK_1:
                keypad[1] = 0;
                break;
            case SDLK_2:
                keypad[2] = 0;
                break;
            case SDLK_3:
                keypad[3] = 0;
                break;
            case SDLK_q:
                keypad[4] = 0;
                break;
            case SDLK_w:
                keypad[5] = 0;
                break;
            case SDLK_e:
                keypad[6] = 0;
                break;
            case SDLK_a:
                keypad[7] = 0;
                break;
            case SDLK_s:
                keypad[8] = 0;
                break;
            case SDLK_d:
                keypad[9] = 0;
                break;
            case SDLK_y:
                keypad[10] = 0;
                break;
            case SDLK_c:
                keypad[11] = 0;
                break;
            case SDLK_4:
                keypad[12] = 0;
                break;
            case SDLK_r:
                keypad[13] = 0;
                break;
            case SDLK_f:
                keypad[14] = 0;
                break;
            case SDLK_v:
                keypad[15] = 0;
                break;
            }
            break;
        }
    }

    return true;
}
