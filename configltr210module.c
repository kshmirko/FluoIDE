#include "configltr210module.h"
#define MAX_SYNC_MODES 9
#define MAX_ADC_MODES 3
#define MAX_ADC_RANGES 5
#define MAX_CHANNELS 128
#define ZERO_OFFSET_CHOICE 2



void configltr210(CDKSCREEN* cdkscreen) {

	CDKITEMLIST *syncmode = 0;
	CDKITEMLIST *inputmode = 0;
	CDKENTRY	*entfreq = 0;
	CDKENTRY	*entmeastime = 0;
	CDKENTRY	*enthisttime = 0;
	CDKENTRY	*entreqblocks = 0, *entreprate=0;
	CDKRADIO 	*radio = 0;
	CDKSCROLL *channels = 0;
	CDKBUTTONBOX *buttonWidget   = 0;
	
	CDKRADIO 	*ch1en = 0;
	CDKITEMLIST *ch1rng= 0;
	CDKITEMLIST *ch1mod= 0;
	CDKRADIO 	*ch2en = 0;
	CDKITEMLIST *ch2rng= 0;
	CDKITEMLIST *ch2mod= 0;

	const char * ENDIS[] = {
		"Disabled",
		"Enabled"
	};

	const char * SYNC_MODES[] = {
		"INTERNAL",
		"CH1 RISE",
		"CH1 FALL",
		"CH2 RISE",
		"CH2 FALL",
		"SYNC IN RISE",
		"SYNC IN FALL",
		"PERIODIC",
		"CONTINUOUS",
	}; 

	const char * CHMODES[] = {
			"ACDC",
			"AC",
			"ZERO"
	};

	const char * CHRANGES[] = {
		"10V",
		"5V",
		"2V",
		"1V",
		"0.5V"
	};

	const char *buttons[] = {
		" OK ",
		" Edit ",
		" Cancel "
	};

	const char *zeroOffset[] = {
		"SKIP",
		"ZERO OFFSET"
	};


	char **chlistitems=NULL;	

	syncmode = newCDKItemlist(cdkscreen, 
			10,
			2,
			"</L/U/32>Adc sync mode:     <!32>",
			NULL,
			(CDK_CSTRING2)SYNC_MODES,
			MAX_SYNC_MODES,
			0,
			TRUE,
			FALSE);

	enthisttime = newCDKEntry(cdkscreen, 32, 2,
		"</L/U/32>History time (mks):<!32>", NULL,
		A_NORMAL, '.', vMIXED,
		10, 1, 10,
		TRUE, FALSE);

	entmeastime = newCDKEntry(cdkscreen, 54, 2,
		"</L/U/32>Meas.  time  (mks):<!32>", NULL,
		A_NORMAL, '.', vMIXED,
		10, 1, 10,
		TRUE, FALSE);
	
	entfreq = newCDKEntry(cdkscreen, 76, 2,
		"</L/U/32>ADC Frequency (Hz):<!32>", NULL,
		A_NORMAL, '.', vINT,
		8, 1, 8,
		TRUE, FALSE);

	radio = newCDKRadio(cdkscreen, 10,6,
		NONE,
		4, 16,
		NULL,
		(CDK_CSTRING2) zeroOffset, ZERO_OFFSET_CHOICE,
		'#' | A_REVERSE, 1,
		A_REVERSE,
		TRUE, FALSE);

	entreqblocks = newCDKEntry(cdkscreen, 32, 6,
		"</L/U/32>Number of   blocks:<!32>", NULL,
		A_NORMAL, '.', vINT,
		8, 1, 8,
		TRUE, FALSE);

	entreprate = newCDKEntry(cdkscreen, 54, 6,
		"</L/U/32>Repitition rate (Hz):<!32>", NULL,
		A_NORMAL, '.', vINT,
		8, 1, 8,
		TRUE, FALSE);

	ch1en = newCDKRadio(cdkscreen, 10,10,
		NONE,
		5, 12,
		"</U>Channel 1",
		(CDK_CSTRING2) ENDIS, ZERO_OFFSET_CHOICE,
		'#' | A_REVERSE, 1,
		A_REVERSE,
		TRUE, FALSE);

	ch2en = newCDKRadio(cdkscreen, 32,10,
		NONE,
		5, 12,
		"</U>Channel 2",
		(CDK_CSTRING2) ENDIS, ZERO_OFFSET_CHOICE,
		'#' | A_REVERSE, 1,
		A_REVERSE,
		TRUE, FALSE);

	ch1rng = newCDKItemlist(cdkscreen, 
			10,
			15,
			"</L/U/32>ADC Range:<!32>",
			NULL,
			(CDK_CSTRING2)CHRANGES,
			MAX_ADC_RANGES,
			0,
			TRUE,
			FALSE);

	ch2rng = newCDKItemlist(cdkscreen, 
			32,
			15,
			"</L/U/32>ADC Range:<!32>",
			NULL,
			(CDK_CSTRING2)CHRANGES,
			MAX_ADC_RANGES,
			0,
			TRUE,
			FALSE);

	ch1mod = newCDKItemlist(cdkscreen, 
			10,
			20,
			"</L/U/32>ADC Mode:<!32>",
			NULL,
			(CDK_CSTRING2)CHMODES,
			MAX_ADC_MODES,
			0,
			TRUE,
			FALSE);

	ch2mod = newCDKItemlist(cdkscreen, 
			32,
			20,
			"</L/U/32>ADC Mode:<!32>",
			NULL,
			(CDK_CSTRING2)CHMODES,
			MAX_ADC_MODES,
			0,
			TRUE,
			FALSE);

	
	
	buttonWidget = newCDKButtonbox (cdkscreen, 10, 32,
				   1, 40,
				   NULL, 1, 3,
				   (CDK_CSTRING2) buttons, 3, A_REVERSE,
				   TRUE, FALSE);



	drawCDKItemlist(syncmode, 1);
	drawCDKEntry(enthisttime, 1);
	drawCDKEntry(entmeastime, 1);
	drawCDKEntry(entfreq, 1);
	drawCDKRadio(radio, 1);
	drawCDKEntry(entreqblocks, 1);
	drawCDKEntry(entreprate, 1);
	drawCDKRadio(ch1en, 1);
	drawCDKRadio(ch2en, 1);
	drawCDKItemlist(ch1rng, 1);
	drawCDKItemlist(ch2rng, 1);
	drawCDKItemlist(ch1mod, 1);
	drawCDKItemlist(ch2mod, 1);

	drawCDKButtonbox(buttonWidget, 1);


	int decision = 0;
	int sync_id, freq, nblocks, ch1rng_id, ch2rng_id, ch1mod_id, ch2mod_id, zero;
	int ch1en_id, ch2en_id, reprate_id;
	double histt, meast;
	
	do{
		sync_id = activateCDKItemlist(syncmode, 0);
		histt = atof(activateCDKEntry(enthisttime, 0));
		meast = atof(activateCDKEntry(entmeastime, 0));
		freq = atoi(activateCDKEntry(entfreq, 0));
		zero = activateCDKRadio(radio,0);
		nblocks = atoi(activateCDKEntry(entreqblocks,0));
		reprate_id = atoi(activateCDKEntry(entreprate,0));
		ch1en_id = activateCDKRadio(ch1en, 0);
		ch1rng_id = activateCDKItemlist(ch1rng, 0);
		ch1mod_id = activateCDKItemlist(ch1mod, 0);

		ch2en_id = activateCDKRadio(ch2en, 0);
		ch2rng_id = activateCDKItemlist(ch2rng, 0);
		ch2mod_id = activateCDKItemlist(ch2mod, 0);
		decision = activateCDKButtonbox(buttonWidget,0);

	}while(decision==1 || decision==-1);
	
	

	if(decision==0) {
		FILE* f = NULL;
		if((f=fopen("config.ltr210", "wt"))!=NULL) {
		
			fprintf(f, "SYNC MODE: %d\n", sync_id);
			fprintf(f, "FLAGS: %d\n", 3);
			fprintf(f, "HISTORY TIME (mks): %d\n", (int)histt);
			fprintf(f, "MEASUREMENTS TIME (mks): %d\n", (int)meast);
			fprintf(f, "FREQUENCY: %d Hz\n", freq);
			fprintf(f, "MEAS ZERO OFFSET: %d\n", zero);
			fprintf(f, "REQUIRED BLOCKS : %d\n", nblocks);
			fprintf(f, "CH[0].Enabled: %d\n", ch1en_id);
			fprintf(f, "CH[0].Range: %d\n", ch1rng_id);
			fprintf(f, "CH[0].Mode: %d\n", ch1mod_id);
			fprintf(f, "CH[1].Enabled: %d\n", ch2en_id);
			fprintf(f, "CH[1].Range: %d\n", ch2rng_id);
			fprintf(f, "CH[1].Mode: %d\n", ch2mod_id);
			fprintf(f, "FRAME FREQ: %d Hz\n", reprate_id);

			fclose(f);
		}
	}


	destroyCDKItemlist(syncmode);
	destroyCDKEntry(enthisttime);
	destroyCDKEntry(entmeastime);
	destroyCDKEntry(entfreq);
	destroyCDKRadio(radio);
	destroyCDKEntry(entreqblocks);
	destroyCDKEntry(entreprate);
	destroyCDKButtonbox(buttonWidget);
	destroyCDKRadio(ch1en);
	destroyCDKRadio(ch2en);
	destroyCDKItemlist(ch1rng);
	destroyCDKItemlist(ch2rng);
	destroyCDKItemlist(ch1mod);
	destroyCDKItemlist(ch2mod);
}
