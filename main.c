#include "fluomenu.h"
#include "about.h"
#include "configdev.h"
#include "configltr11module.h"
#include "configltr210module.h"
#include <cdk.h>
#include <locale.h>


int main(int argc, char* argv[])
{
	CDKSCREEN *cdkscreen = 0;
	WINDOW *cursesWin = 0;
	CDKMENU *menu = 0;
	const char* mesg[10];
	char *fldev=NULL, *spdev=NULL;
	
	//Setup CDK
	cursesWin = initscr();
	cdkscreen = initCDKScreen(cursesWin);
	setlocale(LC_ALL, "");
	setlocale(LC_NUMERIC, "C");
	//start cdk color
	initCDKColor();

	menu = makeMenu(cdkscreen);
	
	refreshCDKScreen(cdkscreen);

	//drawCDKMenu(menu, TRUE);


	for(;;) {
		//Run menu- main widget of the window
		int selection = activateCDKMenu(menu, 0);
		
		if(selection==M_EXIT) {
			break;
		}else 
		if (selection==M_CONFIG_DEVICES) {
			configdev(cdkscreen, &fldev, &spdev);
		}else
		if (selection==M_CONFIG_FLUO) {
			about(cdkscreen);
		}else
		if (selection==M_CONFIG_LTR11) {
			configltr11(cdkscreen);
		}else
		if (selection==M_CONFIG_LTR210) {
			configltr210(cdkscreen);
		}else
		if (selection==M_HELP_ABOUT) {
			about(cdkscreen);
		}
	}


	if(fldev)
		freeChar(fldev);

	if(spdev)
		freeChar(spdev);

	if(menu) {
		destroyCDKMenu(menu);
		menu=NULL;
	}
	if(cdkscreen) {
		destroyCDKScreen(cdkscreen);
		cdkscreen=NULL;
	}

	endCDK();

	return EXIT_SUCCESS;
}

