#pragma once
#include <stdexcept>
#include <string>
#include <SDL2/SDL.h>

void poll_events();

struct Renderer{
    Renderer(
        const std::string& name, 
        uint32_t bw, uint32_t bh,
        uint32_t ww, uint32_t wh
    );
    ~Renderer();
    void destroy();
    void bulk_send_data(const uint8_t* data);
    void send_data(const uint8_t* data, uint64_t count);
    void begin_drawing();
    void finalize();
    bool poll_events();
protected:
    uint32_t bw, bh;
    uint32_t ww, wh;
    uint8_t* date_ref;
    uint32_t pitch;
    SDL_Texture* sdl_text;
    SDL_Window* sdl_win;
    SDL_Renderer* sdl_rend;
};