#include "renderer/renderer.h"
#include<cstring>

int main(){
    Renderer renderer{"some title", 32, 32, 480, 320};
    uint8_t data[32*32];
    std::memset(data, 0xFFFFFFFF, sizeof(data));
    while(renderer.poll_events()){
        renderer.bulk_send_data(data);
        renderer.finalize();
    }
}