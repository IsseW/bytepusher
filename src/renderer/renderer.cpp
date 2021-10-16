#include "renderer.h"
#include <stdexcept>
#include <array>
#include <stack>
#include <cstring>
#include <SDL2/SDL.h>
#define MAX_RENDERER_COUNT 256

namespace ErrStr{
    const char NON_INITIALIZED[] = "Renderer has not been initialized!\n";
}

std::array<SDL_Window*,     MAX_RENDERER_COUNT>     windows;
std::array<SDL_Renderer*,   MAX_RENDERER_COUNT>     renderers;
std::array<SDL_Texture*,    MAX_RENDERER_COUNT>     textures;
std::stack<uint32_t> empty_indexes;
bool is_init = false;

void init_backend(){
    if(!is_init){
        SDL_Init(SDL_INIT_VIDEO);
        for(uint32_t i = 0; i < MAX_RENDERER_COUNT; ++i){
            empty_indexes.push(i);
        }
        is_init = true;
    }
}

Renderer::Renderer(const std::string& name, uint32_t width, uint32_t height): 
    width{width}, height{height}
{
    init_backend();
    index = empty_indexes.top();
    empty_indexes.pop();
    SDL_CreateWindowAndRenderer(width, height, 0, &windows[index], &renderers[index]);
    textures[index] = SDL_CreateTexture(renderers[index], SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_TARGET, width, height);
}

Renderer::~Renderer(){
    SDL_DestroyWindow(windows[index]);
    SDL_DestroyTexture(textures[index]);
    SDL_DestroyRenderer(renderers[index]);
    empty_indexes.push(index);
}

void Renderer::bulk_send_data(const uint8_t* data){
    SDL_UpdateTexture(textures[index], nullptr, data, width);
}

void Renderer::send_data(const uint8_t* data, uint64_t count){
    std::memcpy(this->date_ref, data, count);
}

void Renderer::begin_drawing(){
    SDL_LockTexture(textures[index], nullptr, (void**)&this->date_ref, (int*)&this->pitch);
}

void Renderer::finalize(){
    SDL_UnlockTexture(textures[index]);
    SDL_SetRenderDrawColor(renderers[index], 0, 0, 0, 0);
    SDL_RenderClear(renderers[index]);
    SDL_RenderCopy(renderers[index], textures[index], nullptr, nullptr);
    SDL_RenderPresent(renderers[index]);
}

void poll_events(){
    SDL_PumpEvents();
}