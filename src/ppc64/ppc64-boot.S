/*
// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot
*/

.balign 4
.section .text

.global nb_reset_vector

nb_reset_vector:
	bl	.Laddr			/* get current address */
.Laddr:
	mflr	4			/* real address of .Laddr */
	lwz	0,(.Lstk-.Laddr)(4)	/* stack address location */
	mr	1,0			/* use user defined stack */

	addi	1,1,-4		/* make sure we don't overwrite debug mem */
	lis	0,0
	stw	0,0(1)		/* clear back chain */
	stwu	1,-64(1)		/* push another stack frame */

	/* Let her rip */

	bl 	nb_init_hw
	/* finally execute the firmware */
	bl	nb_start_exec
	/* return value from main is argument to exit */
	bl	nb_reset_vector

	trap

.global nb_start_rom
.global nb_start_context
.global nb_boot_processor_ready

.equ NB_BOOT_ADDR, 0x1030000

nb_start_rom:
	lis 3, NB_BOOT_ADDR@h
	addi 3, 3, NB_BOOT_ADDR@l

	blr

nb_start_context:
	li 4, 0
	cmp 0, 0, 4, 3
	blt run_context
	mr 3, 31
	blr
run_context:
	blr /* r3 is filled here */

.Lstk:
/*	.long	__stack*/
	.long	stack_top

.data

nb_boot_processor_ready:
	.word 0
