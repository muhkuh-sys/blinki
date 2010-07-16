
#include <string.h>

#include "main.h"

#include "i2c_hifsta.h"
#include "netx_io_areas.h"
#include "systime.h"

#include "uart.h"
#include "uprintf.h"

#include "serial_vectors.h"

/*-------------------------------------------------------------------------*/


static const UART_CONFIGURATION_T tUartCfg_nxhx10_etm =
{
        .uc_rx_mmio = 20U,
        .uc_tx_mmio = 21U,
        .uc_rts_mmio = 0xffU,
        .uc_cts_mmio = 0xffU,
        .us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};


void blinki_main(void) __attribute__ ((noreturn));
void blinki_main(void)
{
	BLINKI_HANDLE_T tBlinkiHandle;


	systime_init();
	i2c_hifsta_init();
	uart_init(0, &tUartCfg_nxhx10_etm);

	uprintf("*** hallo! ***\n");

	/* Switch all leds off. */
	i2c_hifsta_rdy_off_run_off();

	tBlinkiHandle.ulMask     = 0x00000055;
	tBlinkiHandle.ulState    = 0x00000150;
	tBlinkiHandle.ulTimer    = 0;
	tBlinkiHandle.uiPosition = 0;
	while(1)
	{
		blinki(&tBlinkiHandle);
		uprintf("blinki at %dms.\n", systime_get_ms());
	}
}

