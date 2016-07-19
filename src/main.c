
#include <string.h>

#include "netx_io_areas.h"
#include "rdy_run.h"
#include "systime.h"
#include "uart_standalone.h"
#include "uprintf.h"
#include "version.h"

/*-------------------------------------------------------------------------*/

/* 'NXBL' DPM boot identifier ('NXBL') */
#define HBOOT_DPM_ID_LISTENING          0x4c42584e
/* This is some other string to overwrite the boot identifier. */
#define HBOOT_DPM_ID_OVERWRITE          0x33323130

#if ASIC_TYP==56
extern volatile unsigned long aulDpmStart[16384];
#elif ASIC_TYP==4000
extern volatile unsigned long aulPcieDpmStart[16384];
#endif


void blinki_main(void);
void blinki_main(void)
{
	BLINKI_HANDLE_T tBlinkiHandle;
	unsigned long ulValue;


	systime_init();
	uart_standalone_initialize();

	uprintf("\f. *** Blinki by doc_bacardi@users.sourceforge.net ***\n");
	uprintf("V" VERSION_ALL "\n\n");

#if ASIC_TYP==56
	/* Overwrite the DPM boot cookie to show the host that the firmware started. */
	if( aulDpmStart[0x40]==HBOOT_DPM_ID_LISTENING )
	{
		aulDpmStart[0x40] = HBOOT_DPM_ID_OVERWRITE;
	}
#elif ASIC_TYP==4000
	/* Overwrite the DPM boot cookie to show the host that the firmware started. */
	if( aulPcieDpmStart[0x40]==HBOOT_DPM_ID_LISTENING )
	{
		aulPcieDpmStart[0x40] = HBOOT_DPM_ID_OVERWRITE;
	}
#endif


	/* Switch all LEDs off. */
	rdy_run_setLEDs(RDYRUN_OFF);

	rdy_run_blinki_init(&tBlinkiHandle, 0x00000055, 0x00000150);
	do
	{
		rdy_run_blinki(&tBlinkiHandle);
		uprintf("blinki at %dms.\n", systime_get_ms());

#if ASIC_TYP==4000
		ulValue = aulPcieDpmStart[0x40];
		ulValue ^= HBOOT_DPM_ID_OVERWRITE;
#else
		ulValue = 1;
#endif
	} while( ulValue!=0 );
}

