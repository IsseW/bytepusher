#include "renderer.h"
#include <stdexcept>
#include <array>
#include <stack>
#include <cstring>
#define MAX_RENDERER_COUNT 256

namespace ErrStr{
    const char NON_INITIALIZED[] = "Renderer has not been initialized!\n";
}

bool is_init = false;

void init_backend(){
    if(!is_init){
        SDL_Init(SDL_INIT_VIDEO);
        is_init = true;
    }
}

void Renderer::set_manual_event_hanlder(ManualEventHandler meh){
    this->meh = meh;
}

Renderer::Renderer(
    const std::string& name, 
    uint32_t bw, uint32_t bh,
    uint32_t ww, uint32_t wh
):  bw{bw}, bh{bh},
    ww{ww}, wh{wh} 
{
    init_backend();
    SDL_CreateWindowAndRenderer(ww, wh, 0, &sdl_win, &sdl_rend);
    sdl_text = SDL_CreateTexture(sdl_rend, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_TARGET, bw, bh);
}

Renderer::~Renderer(){
    destroy();
}

void Renderer::destroy(){
    SDL_DestroyTexture(sdl_text);
    SDL_DestroyRenderer(sdl_rend);
    SDL_DestroyWindow(sdl_win);
}

void Renderer::bulk_send_data(const uint8_t* data){
    SDL_UpdateTexture(sdl_text, nullptr, data, bw);
}

void Renderer::send_data(const uint8_t* data, uint64_t count){
    std::memcpy(this->date_ref, data, count);
}

void Renderer::begin_drawing(){
    SDL_LockTexture(sdl_text, nullptr, (void**)&this->date_ref, (int*)&this->pitch);
}

void Renderer::finalize(){
    SDL_UnlockTexture(sdl_text);
    SDL_SetRenderDrawColor(sdl_rend, 0, 0, 0, 0);
    SDL_RenderClear(sdl_rend);
    SDL_RenderCopy(sdl_rend, sdl_text, nullptr, nullptr);
    SDL_RenderPresent(sdl_rend);
}

bool Renderer::poll_events(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(meh)
            meh(event);
        switch(event.type){
        case SDL_QUIT:
            destroy();
            return false;
        }
    }
    return true;
}