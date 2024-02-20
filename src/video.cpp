#include "video.h"

#define GPU_CLEAR_COLOR 0x000000FF

Video::Video(uint32_t w, uint32_t h) : width(w), height(h) {
    framebuffer.resize(width * height * 4, 0);
}

Video::~Video() {}

void Video::clearScreen() {
    memset(framebuffer.data(), GPU_CLEAR_COLOR, width * height * 4);
}

void Video::update() {
    // TODO: Draw pixels on the framebuffer
}
