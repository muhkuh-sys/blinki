	.section .init_code, "ax"
	.arm

	.extern test_main
	.extern stack_top

	.global start

@--------------------------------------

    .func start, start
    .type start, STT_FUNC
start:
	push    {r1, r2, r3, r4, lr}

	@ Remember the ROM stack position.
	mov     r1, sp

	@ Set own stack position.
	ldr     r2, =stack_top
	mov     sp, r2

	@ Store the ROM stack position on the new stack.
	push    {r1}

#if ASIC_TYP==10
	@ copy the data section
	ldr     r1, =__data_loadaddr__
	ldr     r2, =__data_start__
	ldr     r3, =__data_end__
copy_data:
	cmp     r2, r3
	ldrlo   r4, [r0], #4
	strlo   r4, [r1], #4
	blo     copy_data
#endif

	@ Clear the .bss section (zero init).
	mov     r1, #0
	ldr     r2, =__bss_start__
	ldr     r3, =__bss_end__
clear_bss:
	cmp     r2, r3
	strlo   r1, [r2], #4
	blo     clear_bss

	bl      blinki_main

	@ Restore the ROM stack position.
	pop     {r1}
	mov     sp, r1

	@ Restore the registers.
	pop     {r1, r2, r3, r4, pc}

    .endfunc

@--------------------------------------

  .end

