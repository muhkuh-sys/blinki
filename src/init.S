	.section .init_code, "ax"

	.extern blinki_main
	.extern stack_top

	.global start

#include "asic_types.h"

@--------------------------------------

@ The Cortex-M4 in the netX90 is a THUMB-only CPU.
@ All others start in 32 bit mode.
#if ASIC_TYP==ASIC_TYP_NETX90_MPW || ASIC_TYP==ASIC_TYP_NETX90_MPW_APP || ASIC_TYP==ASIC_TYP_NETX90 || ASIC_TYP==ASIC_TYP_NETX90_APP
	.syntax unified
	.thumb
#else
	.arm
#endif


    .func start, start
    .type start, STT_FUNC
start:
	push    {r0, r1, r2, r3, lr}

	/* Save the stack position of the ROM. */
	mov     r1, sp

	@ Set own stack position.
	ldr     r2, =stack_top
	mov     sp, r2

	/* Save the ROM stack position. */
	push    {r1}

	@ Clear the .bss section (zero init).
	mov     r1, #0
	ldr     r2, =__bss_start__
	ldr     r3, =__bss_end__
clear_bss:
	str     r1, [r2], #4
	cmp     r2, r3
	bmi     clear_bss

	blx     blinki_main
	
	/* Restore the ROM stack position. */
	pop     {r1}
	mov     sp, r1

	/* Restore the rest of the registers. */
	pop     {r0, r1, r2, r3, lr}
	bx      lr
    .endfunc

@--------------------------------------

  .end

