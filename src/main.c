
#include <string.h>

#include "hboot_dpm.h"
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


void blinki_main(void *pvBootBlock, unsigned long ulBootSource);
void blinki_main(void *pvBootBlock __attribute__((unused)), unsigned long ulBootSource)
{
	BLINKI_HANDLE_T tBlinkiHandle;
	int iBootSourceIsDPM;


	systime_init();
	uart_standalone_initialize();

	uprintf("\f. *** Blinki by doc_bacardi@users.sourceforge.net ***\n");
	uprintf("V" VERSION_ALL "\n\n");

	/* Was this program booted from DPM? */
	iBootSourceIsDPM = hboot_dpm_is_bootsource_dpm(ulBootSource);
	if( iBootSourceIsDPM!=0 )
	{
		/* Yes, it came from the DPM.
		 * Notify the host that the software has started.
		 */
		hboot_dpm_show_software_start(ulBootSource);
	}

	/* Switch all LEDs off. */
	rdy_run_setLEDs(RDYRUN_OFF);

	rdy_run_blinki_init(&tBlinkiHandle, 0x00000055, 0x00000150);
	while(1)
	{
		rdy_run_blinki(&tBlinkiHandle);
		uprintf("blinki at %dms.\n", systime_get_ms());
	};
}

