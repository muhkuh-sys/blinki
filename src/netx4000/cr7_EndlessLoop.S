
	.section .init_code, "ax"
	.arm

	.extern test_main
	.extern stack_top

	.global start

@--------------------------------------

  .func start

start:

@ =====================================================================
@
@ The WFE loop.
@   put the CR7 into a kind-of power down mode.
@   This is useful if only the A9 is running.
@
@ =====================================================================

WFE_Loop:
	wfe
	b       WFE_Loop

  .endfunc

@--------------------------------------

  .end

