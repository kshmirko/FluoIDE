#include "about.h"


void about(CDKSCREEN *cdkscreen) {
	const char *mesg[4];
	mesg[0] = "<C>About";
	mesg[1] = "<C><#HL(31)>";
	mesg[2] = "<C></40>Fluorimeter control application<!40>";
	mesg[3] = "<C></32>Copyrights Shmirko K.A.<!32>";
	popupLabel(cdkscreen, (CDK_CSTRING2)mesg, 4);	
}

