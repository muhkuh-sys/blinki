/*---------------------------------------------------------------------------
  Author : Christoph Thelen

           Hilscher GmbH, Copyright (c) 2015, All Rights Reserved

           Redistribution or unauthorized use without expressed written
           agreement from the Hilscher GmbH is forbidden
		   
  netX 4000 RAP UART driver for RAP UART test.
  Based on console_driver_rap_uart.c from the romcode.
  25 mar 2015 SL created
---------------------------------------------------------------------------*/


#include "driver_rap_uart.h"
#include <stddef.h>
#include <string.h>
#include "netx_io_areas.h"

#define ARRAYSIZE(a) (sizeof(a)/sizeof((a)[0]))

/* Note: PortControl is not configured. This will have to be done for the real netx 4000. */
typedef union RAP_UART_PORT_CONTROL_UNION
{
	struct RAP_UART_PORT_CONTROL_STRUCT
	{
		unsigned short usRx;
		unsigned short usTx;
		unsigned short usRts;
		unsigned short usCts;
	} s;
	unsigned short aus[4];
} RAP_UART_PORT_CONTROL_T;


typedef struct
{
	HOSTADEF(S_RAP_UART) * const ptArea;
	RAP_UART_PORT_CONTROL_T tPortControlIndex;
} RAP_UART_INSTANCE_T;


static const RAP_UART_INSTANCE_T atRapUartInstances[] =
{
	{
		.ptArea = (HOSTADEF(S_RAP_UART) * const)Addr_NX4000_RAP_UART0,
		.tPortControlIndex =
		{
			.s =
			{
				.usRx  = PORTCONTROL_INDEX( 4, 10),
				.usTx  = PORTCONTROL_INDEX( 4, 11),
				.usRts = PORTCONTROL_INDEX( 4, 13),
				.usCts = PORTCONTROL_INDEX( 4, 12)
			}
		}
	},

	{
		.ptArea = (HOSTADEF(S_RAP_UART) * const)Addr_NX4000_RAP_UART1,
		.tPortControlIndex =
		{
			.s =
			{
				.usRx  = PORTCONTROL_INDEX( 4, 14),
				.usTx  = PORTCONTROL_INDEX( 4, 15),
				.usRts = PORTCONTROL_INDEX( 5,  1),
				.usCts = PORTCONTROL_INDEX( 5,  0)
			}
		}
	},

	{
		.ptArea = (HOSTADEF(S_RAP_UART) * const)Addr_NX4000_RAP_UART2,
		.tPortControlIndex =
		{
			.s =
			{
				.usRx  = PORTCONTROL_INDEX( 5,  2),
				.usTx  = PORTCONTROL_INDEX( 5,  3),
				.usRts = 0xffff,
				.usCts = 0xffff
			}
		}
	},

	{
		.ptArea = (HOSTADEF(S_RAP_UART) * const)Addr_NX4000_RAP_UART3,
		.tPortControlIndex =
		{
			.s =
			{
				.usRx  = PORTCONTROL_INDEX( 5,  4),
				.usTx  = PORTCONTROL_INDEX( 5,  5),
				.usRts = 0xffff,
				.usCts = 0xffff
			}
		}
	}
};


int rap_uart_open(unsigned int uiUartUnit, const RAP_UART_CONFIGURATION_T *ptCfg)
{
//	unsigned long ulValue;
	unsigned short usValue;
	HOSTADEF(S_RAP_UART) *ptRapUartArea;
	int fUseRtsCts;
	int iResult;


	/* Expect an error. */
	iResult = -1;

	if( uiUartUnit<ARRAYSIZE(atRapUartInstances) )
	{
		
		/* Get the UART area. */
		ptRapUartArea = atRapUartInstances[uiUartUnit].ptArea;

		/* Disable the UART. */
		ptRapUartArea->usRAP_UART_UARTCR = 0;

		/* Set the baud rate. */
		/* FIXME: Set the I/FBRD register directly from the us_baud_div value. 
		   Place the default from the specification for 115200 into the options, select the slower value with ASIC_ENV. */
//		ulValue = ptCfg->us_baud_div;

		/* For ASIC: */
		ptRapUartArea->usRAP_UART_UARTIBRD = 54;
		ptRapUartArea->usRAP_UART_UARTFBRD = 16;

		/* For FPGA: */
//		ptRapUartArea->usRAP_UART_UARTIBRD = 5;
//		ptRapUartArea->usRAP_UART_UARTFBRD = 27;

		/* Set UART to 8N1, FIFO enabled. */
		usValue  = ptCfg->uc_mode;
		/* Use RTS/CTS? */
		fUseRtsCts = ((usValue & RAP_UART_MODE_ENABLE_RTSCTS)!=0);
		/* Extract the bits for the mode register. */
		usValue &= HOSTMSK(RAP_UART_UARTLCR_H_WLEN) | HOSTMSK(RAP_UART_UARTLCR_H_STP2) | HOSTMSK(RAP_UART_UARTLCR_H_EPS) | HOSTMSK(RAP_UART_UARTLCR_H_PEN);
		/* Enable the FIFOs. */
		usValue |= HOSTMSK(RAP_UART_UARTLCR_H_FEN);
		ptRapUartArea->usRAP_UART_UARTLCR_H = usValue;

#if 0
		/* Setup the port control for the RX/TX signals. */
		portcontrol_apply(&(atRapUartInstances[uiUartUnit].tPortControlIndex.s.usRx), &ptCfg->ausPortControl[0], 2);
		
		if( fUseRtsCts!=0 )
		{
			/* Setup the port control for the RTS and CTS signal. */
			portcontrol_apply(&(atRapUartInstances[uiUartUnit].tPortControlIndex.s.usRts), &(ptCfg->ausPortControl[2]), 2);
		}
#endif
		
		/* Enable the UART. */
		usValue  = HOSTMSK(RAP_UART_UARTCR_RXE);
		usValue |= HOSTMSK(RAP_UART_UARTCR_TXE);
		usValue |= HOSTMSK(RAP_UART_UARTCR_UARTEN);
		
		if( fUseRtsCts!=0 )
		{
			usValue |= HOSTMSK(RAP_UART_UARTCR_RTSEn);
			usValue |= HOSTMSK(RAP_UART_UARTCR_CTSEn);
		}
		ptRapUartArea->usRAP_UART_UARTCR = usValue;


		iResult = 0;
	}

	return iResult;
}


unsigned int rap_uart_peek(unsigned int uiUartUnit)
{
	HOSTADEF(S_RAP_UART) *ptRapUartArea;
	unsigned long ulValue;


	/* Get the UART area. */
	ptRapUartArea = atRapUartInstances[uiUartUnit].ptArea;

	/* The UART does not provide an explicit fill level, so the
	 * "RX FIFO Empty" flag must do.
	 */
	ulValue  = (unsigned long)(ptRapUartArea->usRAP_UART_UARTFR);
	ulValue &= HOSTMSK(RAP_UART_UARTFR_RXFE);
	return (ulValue==0) ? 1U : 0U;
}

unsigned char rap_uart_get(unsigned int uiUartUnit)
{
	HOSTADEF(S_RAP_UART) *ptRapUartArea;
	unsigned long ulValue;


	/* Get the UART area. */
	ptRapUartArea = atRapUartInstances[uiUartUnit].ptArea;

	/* Wait for data in the FIFO. */
	do
	{
		ulValue  = (unsigned long)(ptRapUartArea->usRAP_UART_UARTFR);
		ulValue &= HOSTMSK(RAP_UART_UARTFR_RXFE);
	} while( ulValue!=0 );

	/* Get the received byte. */
	return (unsigned char)ptRapUartArea->usRAP_UART_UARTDR;
}



void rap_uart_put(unsigned int uiUartUnit, unsigned char ucChar)
{
	HOSTADEF(S_RAP_UART) *ptRapUartArea;
	unsigned long ulValue;


	/* Get the UART area. */
	ptRapUartArea = atRapUartInstances[uiUartUnit].ptArea;

	/* Wait until there is space in the FIFO. */
	do
	{
		ulValue  = (unsigned long)(ptRapUartArea->usRAP_UART_UARTFR);
		ulValue &= HOSTMSK(RAP_UART_UARTFR_TXFF);
	} while( ulValue!=0 );

	ptRapUartArea->usRAP_UART_UARTDR = (unsigned short)ucChar;
}




void rap_uart_flush(unsigned int uiUartUnit)
{
	HOSTADEF(S_RAP_UART) *ptRapUartArea;
	unsigned long ulValue;


	/* Get the UART area. */
	ptRapUartArea = atRapUartInstances[uiUartUnit].ptArea;

	do
	{
		ulValue  = (unsigned long)(ptRapUartArea->usRAP_UART_UARTFR);
		ulValue &= HOSTMSK(RAP_UART_UARTFR_TXFE);
	} while( ulValue==0 );
}


