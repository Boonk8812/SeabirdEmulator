#ifndef VIDEO_H
#define VIDEO_H

class Video {
private:
    uint32_t width;
    uint32_t height;
    vector<uint8_t> framebuffer;

public:
    Video(uint32_t w, uint32_t h);
    ~Video();
    void clearScreen();
    void update();
};

#endif // VIDEO_H
