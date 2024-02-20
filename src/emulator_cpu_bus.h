#ifndef EMULATOR_CPU_BUS_H
#define EMULATOR_CPU_BUS_H

typedef struct emulator_cpu_bus emulator_cpu_bus_t;

enum emulator_cpu_type {
    EMULATOR_CPU_TYPE_VCPU,          /* Virtual CPU */
    EMULATOR_CPU_TYPE_PHYSICAL_HOST, /* Physical CPU on the host machine */
    EMULATOR_CPU_TYPE_MAX             /* Maximum number of CPU types */
};

struct emulator_cpu_info {
    enum emulator_cpu_type type;
    uint32_t id;
    char name[64];
};

void emulator_cpu_bus_initialize(emulator_cpu_bus_t* bus);
bool emulator_cpu_bus_connect(emulator_cpu_bus_t* bus);
void emulator_cpu_bus_disconnect(emulator_cpu_bus_t* bus);

bool emulator_cpu_bus_is_remote(emulator_cpu_bus_t* bus, uint32_t remote_id);
bool emulator_cpu_bus_connect_remote(emulator_cpu_bus_t* bus, uint32_t remote_id);
void emulator_cpu_bus_disconnect_remote(emulator_cpu_bus_t* bus, uint32_t remote_id);

void emulator_cpu_bus_send_microcode_control_lines(emulator_cpu_bus_t* bus, uint32_t dest_id, const uint8_t* buf, size_t len);
size_t emulator_cpu_bus_receive_microcode_control_lines(emulator_cpu_bus_t* bus, uint32_t src_id, uint8_t* buf, size_t max_len);

void emulator_cpu_bus_send_binary_data(emulator_cpu_bus_t* bus, uint32_t dest_id, const uint8_t* buf, size_t len);
size_t emulator_cpu_bus_receive_binary_data(emulator_cpu_bus_t* bus, uint32_t src_id, uint8_t* buf, size_t max_len);

#endif  // EMULATOR_CPU_BUS_H
