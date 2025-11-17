/* -------------------------------------------

    Copyright (C) 2024, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

.text
.balign 4
.global cb_start_context
.global cb_boot_processor_ready

cb_start_context:
    bl cb_start_context

cb_boot_processor_ready:
    bl cb_boot_processor_ready
