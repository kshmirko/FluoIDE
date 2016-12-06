#include "configdev.h"

/**
	Создает диалоговое окно с двумя полями ввода и тремя кнопками.
	Окно предназначено для установки назуаний системных устройств.
	**fldev - указатель на строку символов, содержащих название 
				устройства для флуориметра
	**fldev - указатель на строку символов, содержащих название 
				устройства для спектрометра

	после выполнения этой функции значения этих переменных изменятся.
	Если будет активирована кнока OK, значения этих переменных изменятся 
	на знеачения полей ввода
	Если будет активирована кнопка Cancel, то эти указатели будут 
	указывать на пустую строкуу
	
*/
void configdev(CDKSCREEN* cdkscreen, char**fldev, char**spdev) {
	CDKENTRY *fluodevice = 0, *spectrodevice = 0;
	CDKBUTTONBOX* buttonWidget=0;
	
	const char *buttons[] = { " Ok ", " Edit ", " Cancel "};

	int selection = 0;

	fluodevice = newCDKEntry(cdkscreen, CENTER, 8,
		"<C></U></32>Setup device names:<!32>", "Fluorimeter device :",
		A_NORMAL, '.', vMIXED,
		40, 0, 256,
		TRUE, FALSE);
	setCDKEntry(fluodevice, *fldev, 0, 256, TRUE);

	spectrodevice = newCDKEntry(cdkscreen, CENTER, 11,
		NULL, "Spectrometer device:",
		A_NORMAL, '.', vMIXED,
		40, 0, 256,
		TRUE, FALSE);	
	setCDKEntry(spectrodevice, *spdev, 0, 256, TRUE);

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
		
		if(selection==1) { // If Cancel pressed free memory
			freeChar(*fldev);
			freeChar(*spdev);
			*spdev=NULL;
			*fldev=NULL;
		}
	}
	while(selection==1); //EDIT BUTTON

	if(selection==2){ //CANCEL BUTTON
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

