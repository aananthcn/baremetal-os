/*
 * Copyright 2026 Aananth C N
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
