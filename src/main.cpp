#include <iostream>
#include "video.h"
#include "main_video_controller.h"

using namespace std;

int main() {
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    Video video(WIDTH, HEIGHT);

    cout << "*** Welcome to the Seabird Emulator ***" << endl;
    cout << "(Type 'clear' to clear the screen.)" << endl;
    cout << "--------------------------------------" << endl;

    bool quit = false;
    string input;

    while (!quit) {
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (input == "clear") {
            video.clearScreen();
        }

        // TODO: Render game frames, process inputs, etc.

        video.update();
    }

    return 0;
}

int main_video() {
    MainVideoController controller;

    controller.initialize();

    // Game loop
    while (true) {
        // Query events, update simulation, etc.

        // Clear screen
        controller.update();

        // Draw frame
        static constexpr uint32_t FRAME_WIDTH = 640;
        static constexpr uint32_t FRAME_HEIGHT = 480;

        uint8_t frameData[FRAME_WIDTH * FRAME_HEIGHT * 4];
        // Fill the frameData array with your frame's content

        controller.drawFrame(frameData, FRAME_WIDTH, FRAME_HEIGHT);
    }

    return 0;
}
