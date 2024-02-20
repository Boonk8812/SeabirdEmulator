#ifndef MAIN_VIDEO_CONTROLLER_H
#define MAIN_VIDEO_CONTROLLER_H

#include "video.h"
#include "vgpu.h"

class MainVideoController {
private:
    static constexpr uint32_t DEFAULT_WIDTH = 800;
    static constexpr uint32_t DEFAULT_HEIGHT = 580;

    Video* video;
    vGPU* vgpu;

public:
    MainVideoController();
    ~MainVideoController();
    void initialize();
    void update();
    void drawFrame(const uint8_t* frameData, uint32_t width, uint32_t height);
};

#endif // MAIN_VIDEO_CONTROLLER_H
