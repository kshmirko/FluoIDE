#include "configltr11module.h"
#define MAX_MODES 3
#define MAX_ADC_MODES 5
#define MAX_RANGES 4
#define MAX_CHANNELS 128


const char * START_MODES[MAX_MODES] = {
	"INTERNAL",
	"EXT RISE",
	"EXT FALL"
}; 

const char * INPUT_MODES[MAX_MODES] = {
	"EXT RISE",
	"EXT FALL",
	"INTERNAL"
}; 

const char * CHMODES[MAX_MODES] = {
		"DIFF",
		"COMM",
		"ZERO"
};

const char * CHRANGES[MAX_RANGES] = {
	"10000MV",
	"2500MV",
	"625MV",
	"156MV"
};

const char *buttons[] = {
	" OK ",
	" Edit ",
	" Cancel "
};

static int addChannelsCB(EObjectType cdktype GCC_UNUSED,
					void *object,
					void *clientData GCC_UNUSED,
					chtype input GCC_UNUSED) {

	CDKSCROLL *s = (CDKSCROLL*)object;
	CDKSCREEN *cdkscreen = ScreenOf(s);
	
	CDKENTRY *chno = 0;
	CDKITEMLIST *chmode = 0;
	CDKITEMLIST *chrange = 0;
	
	
	chno = newCDKEntry(cdkscreen, CENTER, 5,
		"</L/U/40>Channel no:<!40>", NULL,
		A_NORMAL, '.', vINT,
		3, 0, 2,
		TRUE, FALSE);

	chmode = newCDKItemlist(cdkscreen, 
			CENTER,
			10,
			"</L/U/40>Channel mode:<!40>",
			NULL,
			(CDK_CSTRING2)CHMODES,
			MAX_MODES,
			0,
			TRUE,
			FALSE);

	chrange = newCDKItemlist(cdkscreen, 
			CENTER,
			15,
			"</L/U/40>Channel range:<!40>",
			NULL,
			(CDK_CSTRING2)CHRANGES,
			MAX_RANGES,
			0,
			TRUE,
			FALSE);

	drawCDKEntry(chno, 1);
	drawCDKItemlist(chmode, 1);
	drawCDKItemlist(chrange, 1);
	
	int idx = atoi(activateCDKEntry(chno,0));
	int chmodeid = activateCDKItemlist(chmode, 0);
	int chrangeid = activateCDKItemlist(chrange, 0);
	
	static char tmp[30];
	sprintf(tmp, "CH[%d] = (mode = %d, range = %d)", idx, chmodeid,
													chrangeid);

	
	destroyCDKEntry(chno);
	destroyCDKItemlist(chmode);
	destroyCDKItemlist(chrange);
	
	addCDKScrollItem(s, tmp);
	refreshCDKScreen(cdkscreen);

	return TRUE;
	
}

static int delChannelsCB(EObjectType cdktype GCC_UNUSED,
					void *object,
					void *clientData GCC_UNUSED,
					chtype input GCC_UNUSED) {

	CDKSCROLL *s = (CDKSCROLL*)object;
	CDKSCREEN *cdkscreen = ScreenOf(s);
	deleteCDKScrollItem(s, getCDKScrollCurrent(s));
	refreshCDKScreen(cdkscreen);

	return TRUE;
}


void configltr11(CDKSCREEN* cdkscreen) {

	CDKITEMLIST *startmode = 0;
	CDKITEMLIST *inputmode = 0;
	CDKENTRY	*entfreq = 0;
	CDKENTRY	*entmeastime = 0;
	CDKENTRY	*entreqblocks = 0;
	CDKSCROLL *channels = 0;
	CDKBUTTONBOX *buttonWidget   = 0;


	char **chlistitems=NULL;	

	startmode = newCDKItemlist(cdkscreen, 
			10,
			5,
			"</L/U/32>Start adc mode:<!32>",
			NULL,
			(CDK_CSTRING2)START_MODES,
			MAX_MODES,
			0,
			TRUE,
			FALSE);

	inputmode = newCDKItemlist(cdkscreen, 
			10,
			9,
			"</L/U/32>Input adc mode:<!32>",
			NULL,
			(CDK_CSTRING2)START_MODES,
			MAX_MODES,
			0,
			TRUE,
			FALSE);

	entfreq = newCDKEntry(cdkscreen, 10, 13,
		"</L/U/32>ADC Frequenc (Hz):<!32>", NULL,
		A_NORMAL, '.', vINT,
		6, 0, 6,
		TRUE, FALSE);

	entmeastime = newCDKEntry(cdkscreen, 10, 17,
		"</L/U/32>Meas. time (mks):<!32>", NULL,
		A_NORMAL, '.', vINT,
		10, 0, 10,
		TRUE, FALSE);

	entreqblocks = newCDKEntry(cdkscreen, 33, 5,
		"</L/U/32>Req. blocks:<!32>", NULL,
		A_NORMAL, '.', vINT,
		5, 0, 5,
		TRUE, FALSE);

	channels = newCDKScroll(cdkscreen, 53, 5,
		RIGHT,
		10,
		40,
		"</L/U/32>Config channels:<!32>",
		(CDK_CSTRING2)chlistitems,
		0,
		FALSE,
		A_REVERSE,
		TRUE,
		FALSE);

	buttonWidget = newCDKButtonbox (cdkscreen, 53, 20,
				   1, 40,
				   NULL, 1, 3,
				   (CDK_CSTRING2) buttons, 3, A_REVERSE,
				   TRUE, FALSE);

	bindCDKObject(vSCROLL, channels, 'a', addChannelsCB, NULL);
	bindCDKObject(vSCROLL, channels, 'd', delChannelsCB, NULL);
		

	drawCDKItemlist(startmode, 1);
	drawCDKItemlist(inputmode, 1);
	drawCDKEntry(entfreq, 1);
	drawCDKEntry(entmeastime, 1);
	drawCDKEntry(entreqblocks, 1);
	drawCDKScroll(channels, 1);
	drawCDKButtonbox(buttonWidget, 1);

	int decision = 0;
	int choiceadcmode = 0;
	int choiceinpmode = 0;
	int freq=0, nblocks=0, mtime=0;
	do{
		choiceadcmode = activateCDKItemlist(startmode, 0);
		choiceinpmode = activateCDKItemlist(inputmode, 0);
		freq = atoi(activateCDKEntry(entfreq, 0));
		
		mtime = atoi(activateCDKEntry(entmeastime, 0));
		
		nblocks = atoi(activateCDKEntry(entreqblocks, 0));
		
		int asel = activateCDKScroll(channels,0);
		decision = activateCDKButtonbox(buttonWidget,0);

	}while(decision==1 || decision==-1 || choiceadcmode==-1 || choiceinpmode==-1);

	char *chlisttmp[MAX_CHANNELS];
	
	int nChannels = getCDKScrollItems(channels, chlisttmp);
	mvprintw(20,10,"%d", nChannels);

	if(decision==0) {
		FILE* f = NULL;
		if((f=fopen("config.ltr11", "wt"))!=NULL) {
		
			fprintf(f, "START ADC MODE: %d\n", choiceadcmode);
			fprintf(f, "INPUT MODE: %d\n", choiceinpmode);
			fprintf(f, "ADC MODE: %d\n", 0);
			fprintf(f, "FREQUENCY: %d\n", freq);
			fprintf(f, "LOGICAL CHANNELS COUNT: %d\n", nChannels);
			for(int i=0; i<nChannels; i++) {
				fprintf(f, "%s\n", chlisttmp[i]);
			}
			fprintf(f, "MEASUREMENTS TIME (mks): %.1f\n", (double)mtime);
			fprintf(f, "REQUIRED BLOCKS : %d\n", nblocks);

			fclose(f);
		}
	}



	unbindCDKObject(vSCROLL, channels, 'a');
	unbindCDKObject(vSCROLL, channels, 'd');

	CDKfreeStrings(chlistitems);

	destroyCDKItemlist(startmode);
	destroyCDKItemlist(inputmode);
	destroyCDKEntry(entfreq);
	destroyCDKEntry(entmeastime);
	destroyCDKEntry(entreqblocks);
	destroyCDKScroll(channels);
	destroyCDKButtonbox(buttonWidget);
}
