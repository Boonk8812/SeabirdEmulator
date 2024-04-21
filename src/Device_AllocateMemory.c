#include <iostream>

struct RAM_Allocator {};

struct Allocator : public RAM_Allocator {
private:
    constexpr static int MIN_ADDRESS = 0x0000;
    constexpr static int MAX_ADDRESS = 0xFFFF;
    constexpr static int MIN_PRELOADER_MEMORY = 0x000000;
    constexpr static int MAX_PRELOADER_MEMORY = 0xFFFFFF;

public:
    int address;
    int preloader_memory;

    Allocator() : address(MIN_ADDRESS), preloader_memory(MIN_PRELOADER_MEMORY) {}

    bool allocateByte(int& byteLocation, int value) {
        if ((byteLocation >= MIN_ADDRESS && byteLocation <= MAX_ADDRESS) ||
            (byteLocation >= MIN_PRELOADER_MEMORY && byteLocation <= MAX_PRELOADER_MEMORY)) {
            byteLocation = value;
            return true;
        } else {
            std::cout << "Invalid allocation request" << std::endl;
            return false;
        }
    }
};

int main() {
    Allocator allocator;

    // Attempting to allocate bytes
    int allocatedMemory1 = -1;
    if (!allocator.allocateByte(allocatedMemory1, 0x4C)) {
        std::cout << "Failed to allocate memory" << std::endl;
    };

    int allocatedPreloaderMemory1 = -1;
    if (!allocator.allocateByte(allocatedPreloaderMemory1, 0x03F5)) {
        std::cout << "Failed to allocate preloader memory" << std::endl;
    };

    // Outputting the results
    std::cout << "Address: " << hex << allocatedMemory1 << dec << ", Value: " << oct << allocatedMemory1 << dec << endl;
    std::cout << "Preloader Address: " << hex << allocatedPreloaderMemory1 << dec << ", Value: " << oct << allocatedPreloaderMemory1 << dec << endl;

    return 0;
}
