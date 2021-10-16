#pragma once
#include <stdexcept>
#include <string>

void poll_events();

struct Renderer{
    Renderer(const std::string& name, uint32_t width, uint32_t height);
    ~Renderer();
    void bulk_send_data(const uint8_t* data);
    void send_data(const uint8_t* data, uint64_t count);
    void begin_drawing();
    void finalize();
protected:
    uint32_t index, width, height;
    uint8_t* date_ref;
    uint32_t pitch;
};