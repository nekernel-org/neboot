/* -------------------------------------------

    Copyright (C) 2024-2025, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

.section .text
.global nb_reset_vector
nb_reset_vector:
    ldr x0, =0x40080000
    mov sp, x0         
    b nb_start_exec         


