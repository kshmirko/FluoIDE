#include "fluomenu.h"

CDKMENU* makeMenu(CDKSCREEN* cdkscreen) {

	int submenusize[4];
	int menuloc[5];
	CDKMENU *menu = 0;

	menulist[0][0] = "File";
	menulist[0][1] = "Exit";
	submenusize[0] = 2;

	menulist[1][0] = "Setup";
	menulist[1][1] = "Configure devices...";
	menulist[1][2] = "Configure fluorimeter...";
	menulist[1][3] = "Configure LTR-11...";
	menulist[1][4] = "Configure LTR-210...";
	submenusize[1] = 5;


	menulist[2][0] = "Start";
	menulist[2][1] = "Test...";
	submenusize[2] = 2;

	menulist[3][0] = "Help";
	menulist[3][1] = "About...";
	submenusize[3] = 2;


	menuloc[0] = LEFT;
	menuloc[1] = LEFT;
	menuloc[2] = LEFT;
	menuloc[3] = RIGHT;

	menu = newCDKMenu(cdkscreen, menulist, 4, submenusize, menuloc,
						TOP, A_UNDERLINE, A_REVERSE);		
	


	return menu;

}
