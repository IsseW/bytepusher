#include "renderer/renderer.h"
#include<cstring>

int main(){
    Renderer renderer{"some title", 480, 320};
    uint8_t data[480*320];
    std::memset(data, 0xFF, sizeof(data));
    while(true){
        renderer.bulk_send_data(data);
        renderer.finalize();
    }
}