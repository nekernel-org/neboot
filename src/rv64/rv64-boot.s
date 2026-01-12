# // Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
# // Distributed under the Apache Software License, Version 2.0. (See accompanying
# // file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
# // Official repository: https://github.com/nekernel-org/neboot


/* Code starts at 8M, everything below is memory mapped hardware. */

.option norvc

.extern nb_start_exec

.global nb_reset_vector
.global nb_hart_present

.section .init
.align 4

nb_reset_vector:
	.cfi_startproc

	csrr t0, mhartid
	beqz t0, nb_start_exec_asm

	j nb_start_other

	.cfi_endproc

nb_start_exec_asm:
	lw t0, __nb_hart_counter
	lw t1, nb_boot_processor_ready

	not t0, t0

	addi t1, zero, 1

.option push
.option norelax

	la gp, nb_global_pointer

.option pop

	la sp, nb_stack_end

	la t5, _bss_start
	la t6, _bss_end

crt0_bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, crt0_bss_clear


	j nb_start_exec
	j nb_hang

nb_start_other:
	lw t1, nb_boot_processor_ready

nb_start_other_wait:
	beq t1, zero, nb_start_other_wait

	la t0, nb_stack_list
	ld t1, nb_stack_align
	mv sp, t0
	add t0, zero, t1
	j nb_hang

.global nb_start_rom
.global nb_start_context

nb_start_context:
	mv ra, zero
	add ra, zero, a1
	mret

.equ NB_BOOT_ADDR, 0x80020000

nb_start_rom:
	li x5, NB_BOOT_ADDR
	mv ra, zero
	add ra, zero, t0
	mret

nb_hang:
	j nb_start_exec
L0:
	wfi
	j L0

.bss

.align 4
nb_hart_present:
	.long 0

.data

.align 4
nb_stack_list:
	.long nb_memory_end

nb_stack_align:
	.word 0x8000

__nb_max_harts:
	.word 2
