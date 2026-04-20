#ifndef KERNEL_H
#define KERNEL_H

/*
 * Non-preemptive cooperative scheduler.
 *
 * Tasks run to completion or call a yield point.
 * SysTick (configured via board.c:systick_config()) can be used to implement
 * time-slicing by overriding systick_handler() in kernel.c.
 */

void kernel_init(void);
void kernel_start(void);

#endif /* KERNEL_H */
