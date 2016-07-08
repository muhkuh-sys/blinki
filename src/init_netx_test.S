	.section .init_code, "ax"
	.arm

	.extern test_main
	.extern stack_top

	.global start


   @ optional can be used by python script to define individual entry points for cortex CA9 core0/1
#if ASIC_TYP==4000
   @ define entry point for CA9_core0
	.global start_core0
   @ define entry point for CA9_core1
	.global start_core1
#endif

@--------------------------------------

  .func start

   @ optional can be used by python script to define individual entry points for cortex CA9 core0/1
#if ASIC_TYP==4000
   @ define entry point for CA9_core0
start_core0:
   @ define entry point for CA9_core1
start_core1:
#endif

start:

	stmfd   sp!, {r0, r1, r2, lr}

	@ Set own stack position.
	ldr     r0, =stack_top
	mov     sp, r0

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

	@ Clear the .bss section (zero init).
	mov     r0, #0
	ldr     r1, =__bss_start__
	ldr     r2, =__bss_end__
clear_bss:
	cmp     r1, r2
	strlo   r0, [r1], #4
	blo     clear_bss

	b       blinki_main

  .endfunc

@--------------------------------------

  .end

