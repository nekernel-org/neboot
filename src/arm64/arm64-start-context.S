/* -------------------------------------------

    Copyright (C) 2024, Amlal El Mahrouss, all rights reserved.

------------------------------------------- */

.text
.balign 4
.global cb_start_context
.global cb_boot_processor_ready

cb_start_context:
    bl cb_start_context

cb_boot_processor_ready:
    bl cb_boot_processor_ready
