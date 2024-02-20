#include <iostream>
#include "video.h"

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
