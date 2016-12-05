#include "configdev.h"

void configdev(CDKSCREEN* cdkscreen, char**fldev, char**spdev) {
	CDKENTRY *fluodevice = 0, *spectrodevice = 0;
	CDKBUTTONBOX* buttonWidget=0;
	const char *buttons[] = { " Ok ", " Edit ", " Cancel "};

	int selection = 0;

	fluodevice = newCDKEntry(cdkscreen, CENTER, 8,
		NULL, "Fluorimeter device :",
		A_NORMAL, '.', vMIXED,
		40, 0, 256,
		TRUE, FALSE);


	spectrodevice = newCDKEntry(cdkscreen, CENTER, 10,
		NULL, "Spectrometer device:",
		A_NORMAL, '.', vMIXED,
		40, 0, 256,
		TRUE, FALSE);
	

	buttonWidget = newCDKButtonbox(cdkscreen, getbegx(spectrodevice->win),
									getbegy(spectrodevice->win)+spectrodevice->boxHeight-1,
									1, spectrodevice->boxWidth-1,
									0, 1, 3,
									(CDK_CSTRING2) buttons, 3, A_REVERSE, TRUE, FALSE);



	setCDKEntryLLChar (fluodevice, ACS_LTEE);
	setCDKEntryLRChar (fluodevice, ACS_RTEE);
	setCDKEntryULChar (spectrodevice, ACS_LTEE);
    setCDKEntryURChar (spectrodevice, ACS_RTEE);
	setCDKEntryLLChar (spectrodevice, ACS_LTEE);
	setCDKEntryLRChar (spectrodevice, ACS_RTEE);
	setCDKButtonboxULChar (buttonWidget, ACS_LTEE);
    setCDKButtonboxURChar (buttonWidget, ACS_RTEE);

	do{	
		drawCDKEntry(fluodevice, TRUE);
		drawCDKEntry(spectrodevice, TRUE);
		drawCDKButtonbox(buttonWidget, TRUE);
	
		*fldev = copyChar(activateCDKEntry(fluodevice, 0));
		*spdev = copyChar(activateCDKEntry(spectrodevice, 0));
		selection = activateCDKButtonbox(buttonWidget,0);
	}
	while(selection==1);

	if(selection==2){
		freeChar(*fldev);
		freeChar(*spdev);
		*fldev=NULL;
		*spdev=NULL;
	}

	destroyCDKEntry(fluodevice);
	destroyCDKEntry(spectrodevice);
	destroyCDKButtonbox(buttonWidget);

	return;
		
}

