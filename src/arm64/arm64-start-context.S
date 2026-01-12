/* -------------------------------------------

    Copyright (C) 2024, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

.text
.balign 4
.global nb_start_context
.global nb_boot_processor_ready

nb_start_context:
    bl nb_start_context

nb_boot_processor_ready:
    bl nb_boot_processor_ready
