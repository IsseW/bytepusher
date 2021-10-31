#include "renderer/renderer.h"
#include "grid/grid.h"
#include "grid/rules.h"

#include<thread>
#include<cstring>

const uint32_t GRID_WIDTH = 32;
const uint32_t GRID_HEIGHT = 32;
const uint32_t WINDOW_WIDTH = GRID_WIDTH * 10;
const uint32_t WINDOW_HEIGHT = GRID_HEIGHT * 10;
const double TICK_TIME = 1.0;

int main(){
    Renderer renderer{"some title", GRID_WIDTH, GRID_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT};

    Grid grid = Grid(GRID_WIDTH, GRID_HEIGHT);
    grid.set_tile(4, 4, Tile::Alive);
    grid.set_tile(4, 5, Tile::Alive);
    grid.set_tile(4, 6, Tile::Alive);
    grid.set_tile(4, 7, Tile::Alive);
    grid.set_tile(4, 8, Tile::Alive);
    grid.set_tile(4, 9, Tile::Alive);
    grid.set_tile(4, 10, Tile::Alive);

    uint64_t now, last;
    double delta_time = 0;

    double next_tick = TICK_TIME;

    auto callback = [&](const SDL_Event& e) {
        switch (e.type) {
            case SDL_MOUSEBUTTONDOWN: {
                uint32_t x = e.button.x * GRID_WIDTH / WINDOW_WIDTH;
                uint32_t y = e.button.y * GRID_HEIGHT / WINDOW_HEIGHT;
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        grid.set_tile(x, y, Tile::Alive);
                        break;
                    
                }
                break;
            }
        }
    };
    renderer.set_manual_event_handler(callback);

    while(renderer.poll_events()) {
        last = now;
        now = SDL_GetPerformanceCounter();
        delta_time = (now - last) / (double)SDL_GetPerformanceFrequency();

        next_tick -= delta_time;
        if (next_tick < 0.0) {
            next_tick = TICK_TIME;
            grid.update_with_rule(game_of_life_rule);
        }

        renderer.bulk_send_data(grid.get_texture());
        renderer.finalize();
    }
}