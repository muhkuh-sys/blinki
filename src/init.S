	.section .init_code, "ax"
	.arm

	.extern blinki_main
	.extern stack_top

	.global start

@--------------------------------------

    .func start, start
    .type start, STT_FUNC
start:
	@ Set own stack position.
	ldr     r2, =stack_top
	mov     sp, r2

#if ASIC_TYP==10
	@ copy the data section
	ldr     r2, =__data_loadaddr__
	ldr     r3, =__data_start__
	ldr     r4, =__data_end__
copy_data:
	cmp     r3, r4
	ldrlo   r5, [r2], #4
	strlo   r5, [r3], #4
	blo     copy_data
#endif

	@ Clear the .bss section (zero init).
	mov     r2, #0
	ldr     r3, =__bss_start__
	ldr     r4, =__bss_end__
clear_bss:
	cmp     r3, r4
	strlo   r2, [r3], #4
	blo     clear_bss

	b       blinki_main
    .endfunc

@--------------------------------------

  .end

