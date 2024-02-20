#ifndef CPU_INSTANCE_H
#define CPU_INSTANCE_H

#include "emulator_cpu_bus.h"

typedef enum { MODE_4BIT, MODE_8BIT, MODE_16BIT, MODE_32BIT, MODE_64BIT, MODE_INVALID } Mode;

typedef struct {
    emulator_cpu_bus_t *bus;
    Mode mode;
} cpu_instance_t;

cpu_instance_t *cpu_instance_new(Mode mode);
void cpu_instance_delete(cpu_instance_t *self);
void cpu_instance_switch_mode(cpu_instance_t *self, Mode new_mode);
void configure_mode(Mode mode);

#endif /* CPU_INSTANCE_H */
