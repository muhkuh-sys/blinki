
#include <string.h>

#include "main.h"

#include "netx_io_areas.h"
#include "rdy_run.h"
#include "systime.h"

#include "uart.h"
#include "uprintf.h"
#include "version.h"

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
#elif ASIC_TYP==4000
static const UART_CONFIGURATION_T tUartCfg =
{
	.uc_rx_mmio = 26U,
	.uc_tx_mmio = 27U,
	.uc_rts_mmio = 0xffU,
	.uc_cts_mmio = 0xffU,
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#endif


#define IO_UART_UNIT 0

static unsigned char io_uart_get(void)
{
	return (unsigned char)uart_get(IO_UART_UNIT);
}


static void io_uart_put(unsigned int uiChar)
{
	uart_put(IO_UART_UNIT, (unsigned char)uiChar);
}


static unsigned int io_uart_peek(void)
{
	return uart_peek(IO_UART_UNIT);
}


static void io_uart_flush(void)
{
	uart_flush(IO_UART_UNIT);
}


static const SERIAL_COMM_UI_FN_T tSerialVectors_Uart =
{
	.fn =
	{
		.fnGet = io_uart_get,
		.fnPut = io_uart_put,
		.fnPeek = io_uart_peek,
		.fnFlush = io_uart_flush
	}
};


SERIAL_COMM_UI_FN_T tSerialVectors;


#if ASIC_TYP==56
extern volatile unsigned long aulDpmStart[16384];
#endif

void blinki_main(void) __attribute__ ((noreturn));
void blinki_main(void)
{
	BLINKI_HANDLE_T tBlinkiHandle;


	systime_init();
	uart_init(IO_UART_UNIT, &tUartCfg);

	/* Set the serial vectors. */
	memcpy(&tSerialVectors, &tSerialVectors_Uart, sizeof(SERIAL_COMM_UI_FN_T));

	uprintf("\f. *** Blinki by doc_bacardi@users.sourceforge.net ***\n");
	uprintf("V" VERSION_ALL "\n\n");

#if ASIC_TYP==56
	/* Overwrite the DPM boot cookie to show the host that the firmware started. */
	if( aulDpmStart[0x40]==0x4C42584E )
	{
		aulDpmStart[0x40] = 0x33323130;
	}
#endif


	/* Switch all LEDs off. */
	rdy_run_setLEDs(RDYRUN_OFF);

	rdy_run_blinki_init(&tBlinkiHandle, 0x00000055, 0x00000150);
	while(1)
	{
		rdy_run_blinki(&tBlinkiHandle);
		uprintf("blinki at %dms.\n", systime_get_ms());
	}
}

