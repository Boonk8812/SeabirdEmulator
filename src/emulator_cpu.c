// This contains vCPU logic

#include <stdio.h>
#include <string.h>
#include <json.h>
#include <emulator_cpu_bus.h>
#include <iostream>
#include <java.h>

struct seabird_console {
  // Console type (CPU or ASM)
  enum { CONSOLE_TYPE_CPU, CONSOLE_TYPE_ASM } type;

  // Pointer to the associated virtual CPU instance
  struct seabird_virtual_cpu* cpu;

  // Buffer for reading user input
  char input_buf[256];

  // Function pointer for handling user input
  int (*handle_input)(struct seabird_console*, const char*);
};

// Callback function for handling CPU console input
static int handle_cpu_input(struct seabird_console* console, const char* input) {
  // Get a reference to the associated virtual CPU instance
  struct seabird_virtual_cpu* cpu = console->cpu;

  // Send the microcode and control lines to the virtual CPU
  cpu->send_microcode_control_lines((const uint8_t*)input, strlen(input));

  return 0;
}

// Callback function for handling ASM console input
static int handle_asm_input(struct seabird_console* console, const char* input) {
  // Convert the input ASM code to bytes
  uint8_t asm_bytes[256];
  size_t length = convert_asm_to_bytes(input, asm_bytes);

  // Send the assembled byte sequence to the virtual CPU
  console->cpu->send_binary_data(asm_bytes, length);

  return 0;
}

// Utility function for converting input ASM code to bytes
size_t convert_asm_to_bytes(const char* asm_code, uint8_t* output_bytes) {
  // Example conversion for the given input code
  // Actual conversion logic depends on the ISA and encoding scheme
  if (strcmp(asm_code, "e8 e9 jmp $ff") == 0) {
    output_bytes[0] = 0xE8;
    output_bytes[1] = 0xE9;
    output_bytes[2] = 0xFF;
    output_bytes[3] = 0xFF;
    return 3;
  } else if (strcmp(asm_code, "c830 ff13 d6 db \"hello\"") == 0) {
    output_bytes[0] = 0xC8;
    output_bytes[1] = 0x30;
    output_bytes[2] = 0xFF;
    output_bytes[3] = 0x13;
    output_bytes[4] = 0xD6;
    output_bytes[5] = 0xDB;
    memcpy(output_bytes + 6, "hello", 5);
    return 11;
  }
  // ...
  return 0;
}

// Function for parsing JSON configuration data and initializing the virtual CPU
int init_virtual_cpu(const char* json_config) {
  // Parse the JSON configuration data
  struct json_object* config = json_tokener_parse(json_config);
  if (!config) {
    // Handle parse errors gracefully
    fprintf(stderr, "Error parsing JSON configuration data.\n");
    return -1;
  }

  // Extract the requested CPU model and clock rate from the JSON data
  const char* model = json_object_get_string(json_object_object_get(config, "model"));
  int clock_rate = json_object_get_int(json_object_object_get(config, "clock_rate"));

  // Allocate memory for the virtual CPU instance
  struct seabird_virtual_cpu* cpu = malloc(sizeof(*cpu));
  if (!cpu) {
    // Handle allocation failures gracefully
    fprintf(stderr, "Failed to allocate memory for virtual CPU instance.\n");
    return -1;
  }

  // Initialize the virtual CPU instance
  initialize_virtual_cpu(cpu, model, clock_rate);

  // Release the parsed JSON data
  json_object_put(config);

  return 0;
}

// Main entry point for the Seabird/Seabird-Emulator program
int main(int argc, char** argv) {
  // Check for valid input parameters
  if (argc != 2) {
    printf("Usage: %s <JSON configuration>\n", argv[0]);
    exit(-1);
  }

  // Read the JSON configuration data from the command line argument
  const char* json_config = argv[1];

  // Initialize the virtual CPU instance based on the JSON configuration
  if (init_virtual_cpu(json_config)) {
    // Handle initialization failures gracefully
    fprintf(stderr, "Failed to initialize virtual CPU instance.\n");
    exit(-1);
  }

  // Create the CPU console
  struct seabird_console cpu_console = { .type = CONSOLE_TYPE_CPU, .cpu = &java::VirtualCPU::get().bus() };

  // Register the callback function for handling CPU console input
  cpu_console.handle_input = handle_cpu_input;

  // Print usage instructions
  printf("Enter microcode and control lines:\n");

  while (1) {
    // Prompt the user for input
    printf("%s > ", cpu_console.type == CONSOLE_TYPE_CPU ? "CPU" : "ASM");

    // Read the user input
    fgets(cpu_console.input_buf, sizeof(cpu_console.input_buf), stdin);

    // Trim trailing newline character
    cpu_console.input_buf[strcspn(cpu_console.input_buf, "\n")] = '\0';

    // Output the user input for debugging purposes
    std::cout << "[INPUT] " << cpu_console.input_buf << std::endl;

    // Dispatch the input to the appropriate handler function
    int ret = cpu_console.handle_input(&cpu_console, cpu_console.input_buf);

    // Check for errors
    if (ret != 0) {
      std::cerr << "[ERROR] Input processing failed." << std::endl;
    }
  }

  // Clean up allocated memory
  free(cpu);

  return 0;
}
