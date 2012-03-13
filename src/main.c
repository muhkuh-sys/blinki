
#include <string.h>

#include "main.h"

#include "netx_io_areas.h"
#include "rdy_run.h"
#include "systime.h"

#include "uart.h"
#include "uprintf.h"

#include "serial_vectors.h"

/*-------------------------------------------------------------------------*/

#if ASIC_TYP==10
/* NXHX10-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
        .uc_rx_mmio = 20U,
        .uc_tx_mmio = 21U,
        .uc_rts_mmio = 0xffU,
        .uc_cts_mmio = 0xffU,
        .us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#elif ASIC_TYP==56
/* NXHX51-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
        .uc_rx_mmio = 34U,
        .uc_tx_mmio = 35U,
        .uc_rts_mmio = 0xffU,
        .uc_cts_mmio = 0xffU,
        .us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#elif ASIC_TYP==50
/* NXHX50-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
        .uc_rx_mmio = 34U,
        .uc_tx_mmio = 35U,
        .uc_rts_mmio = 0xffU,
        .uc_cts_mmio = 0xffU,
        .us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#elif ASIC_TYP==100 || ASIC_TYP==500
static const UART_CONFIGURATION_T tUartCfg =
{
        .us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#endif


void blinki_main(void) __attribute__ ((noreturn));
void blinki_main(void)
{
	BLINKI_HANDLE_T tBlinkiHandle;


	systime_init();
	uart_init(0, &tUartCfg);

	uprintf("*** hallo! ***\n");

	/* Switch all leds off. */
	rdy_run_setLEDs(RDYRUN_OFF);

	rdy_run_blinki_init(&tBlinkiHandle, 0x00000055, 0x00000150);
	while(1)
	{
		rdy_run_blinki(&tBlinkiHandle);
		uprintf("blinki at %dms.\n", systime_get_ms());
	}
}

