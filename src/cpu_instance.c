#include "cpu_instance.h"
#include "emulator_cpu_bus.h"

cpu_instance_t *cpu_instance_new(Mode mode)
{
    cpu_instance_t *instance = malloc(sizeof(cpu_instance_t));
    instance->bus = emulator_cpu_bus_new();
    instance->mode = mode;
    configure_mode(mode);
    return instance;
}

void cpu_instance_delete(cpu_instance_t *self)
{
    emulator_cpu_bus_delete(self->bus);
    free(self);
}

void cpu_instance_switch_mode(cpu_instance_t *self, Mode new_mode)
{
    // Switching logic to go here
    self->mode = new_mode;
    configure_mode(new_mode);
}

void configure_mode(Mode mode)
{
    (void)mode;
    printf("Running in %d-bit mode\n", mode);
}
