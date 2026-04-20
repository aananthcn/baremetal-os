#include "kernel.h"

void kernel_init(void) {
    /* TODO: initialise task table, ready queue */
}

void kernel_start(void) {
    /* TODO: dispatch first ready task */
    while (1) {
        /* TODO: round-robin cooperative dispatch */
    }
}

/*
 * Override the weak systick_handler from vector_handlers.c.
 * Called at the OS tick rate configured by systick_config().
 */
void systick_handler(void) {
    /* TODO: increment tick counter, unblock delayed tasks */
}
