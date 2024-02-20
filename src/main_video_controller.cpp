#include "main_video_controller.h"

MainVideoController::MainVideoController() : video(nullptr), vgpu(nullptr) {}

MainVideoController::~MainVideoController() {
    delete vgpu;
    delete video;
}

void MainVideoController::initialize() {
    vgpu = new vGPU(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    video = new Video(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

void MainVideoController::update() {
    video->clearScreen();
    video->present();
}

void MainVideoController::drawFrame(const uint8_t* frameData, uint32_t width, uint32_t height) {
    // Scaling or cropping logic could be applied here if needed
    vgpu->setDimensions(width, height);
    memcpy(vgpu->getFramebuffer(), frameData, width * height * 4);
    video->swapBuffers();
}
