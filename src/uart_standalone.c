
#include <string.h>

#include "asic_types.h"
#include "uart_standalone.h"
#include "serial_vectors.h"

#if !defined(CFG_USE_RAP_UART)
#       include "uart.h"
#else
#       include "driver_rap_uart.h"
#endif

/*-------------------------------------------------------------------------*/

#if ASIC_TYP==ASIC_TYP_NETX10
/* NXHX10-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
	.uc_rx_mmio = 20U,
	.uc_tx_mmio = 21U,
	.uc_rts_mmio = 0xffU,
	.uc_cts_mmio = 0xffU,
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};

#elif ASIC_TYP==ASIC_TYP_NETX56
/* NXHX51-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
	.uc_rx_mmio = 4U,
	.uc_tx_mmio = 5U,
	.uc_rts_mmio = 0xffU,
	.uc_cts_mmio = 0xffU,
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};

#elif ASIC_TYP==ASIC_TYP_NETX50
/* NXHX50-ETM */
static const UART_CONFIGURATION_T tUartCfg =
{
	.uc_rx_mmio = 34U,
	.uc_tx_mmio = 35U,
	.uc_rts_mmio = 0xffU,
	.uc_cts_mmio = 0xffU,
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};

#elif ASIC_TYP==ASIC_TYP_NETX500
static const UART_CONFIGURATION_T tUartCfg =
{
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};

#elif ASIC_TYP==ASIC_TYP_NETX4000_RELAXED
#       if !defined(CFG_USE_RAP_UART)
static const UART_CONFIGURATION_T tUartCfg =
{
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};
#       else
static const RAP_UART_CONFIGURATION_T tUartCfg =
{
	.us_baud_div = RAP_UART_BAUDRATE_DIV(RAP_UART_BAUDRATE_115200),
	.uc_mode = RAP_UART_MODE_BYTESIZE_8BIT,
	.ausPortControl =
	{
		PORTCONTROL_CONFIGURATION(REEMUX_2, 0, REEMUX_DRV_06MA, REEMUX_UDC_PULLUP50K),      // RX
		PORTCONTROL_CONFIGURATION(REEMUX_2, 0, REEMUX_DRV_06MA, REEMUX_UDC_PULLUP50K),      // TX
		PORTCONTROL_CONFIGURATION(REEMUX_2, 0, REEMUX_DRV_06MA, REEMUX_UDC_PULLUP50K),      // RTS
		PORTCONTROL_CONFIGURATION(REEMUX_2, 0, REEMUX_DRV_06MA, REEMUX_UDC_PULLUP50K)       // CTS
	}
};

#       endif

#elif ASIC_TYP==ASIC_TYP_NETX90_MPW
static const UART_CONFIGURATION_T tUartCfg =
{
	.us_baud_div = UART_BAUDRATE_DIV(UART_BAUDRATE_115200)
};

#else
#       error "Unsupported ASIC_TYPE!"

#endif


#define IO_UART_UNIT 0

static unsigned char io_uart_get(void)
{
#if !defined(CFG_USE_RAP_UART)
	return (unsigned char)uart_get(IO_UART_UNIT);
#else
	return rap_uart_get(IO_UART_UNIT);
#endif
}


static void io_uart_put(unsigned int uiChar)
{
#if !defined(CFG_USE_RAP_UART)
	uart_put(IO_UART_UNIT, (unsigned char)uiChar);
#else
	rap_uart_put(IO_UART_UNIT, (unsigned char)uiChar);
#endif
}


static unsigned int io_uart_peek(void)
{
#if !defined(CFG_USE_RAP_UART)
	return uart_peek(IO_UART_UNIT);
#else
	return rap_uart_peek(IO_UART_UNIT);
#endif
}


static void io_uart_flush(void)
{
#if !defined(CFG_USE_RAP_UART)
	uart_flush(IO_UART_UNIT);
#else
	rap_uart_flush(IO_UART_UNIT);
#endif
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


void uart_standalone_initialize(void)
{
#if !defined(CFG_USE_RAP_UART)
	uart_init(IO_UART_UNIT, &tUartCfg);
#else
	rap_uart_open(IO_UART_UNIT, &tUartCfg);
#endif

	/* Set the serial vectors. */
	memcpy(&tSerialVectors, &tSerialVectors_Uart, sizeof(SERIAL_COMM_UI_FN_T));
}
