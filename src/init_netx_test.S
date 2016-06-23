
	.section .init_code, "ax"
	.arm

	.extern test_main

	.global NetxTestParameter_Init
	.global start
	.global stack_top

@--------------------------------------

  .func start

start:
	stmfd	sp!, {r0, r1, r2, lr}

	@ save pointer to bootblock
	ldr	r1, =NetxTestParameter_Init
	str	r0, [r1]

	@ set own stack position
	ldr	r0, =stack_top
	mov	sp, r0

#if ASIC_TYP==10
	@ copy the data section
	ldr	r0, =__data_loadaddr__
	ldr	r1, =__data_start__
	ldr	r2, =__data_end__
copy_data:
	cmp	r1, r2
	ldrlo	r3, [r0], #4
	strlo	r3, [r1], #4
	blo	copy_data
#endif

	@ clear .bss section (zero init)
	mov	r0, #0
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__
clear_bss:
	cmp	r1, r2
	strlo	r0, [r1], #4
	blo	clear_bss

	b	blinki_main

  .endfunc

@--------------------------------------

	.align 4

NetxTestParameter_Init:
	.word 0

@--------------------------------------

  .end

