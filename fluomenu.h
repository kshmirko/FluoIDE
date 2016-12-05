#ifndef __FLUOMENU_H__
#define __FLUOMENU_H__

#include <cdk.h>

#define M_EXIT 0
#define M_CONFIG_DEVICES 100
#define M_CONFIG_FLUO 101
#define M_CONFIG_LTR11 102
#define M_CONFIG_LTR210 103
#define M_START_TEST 200
#define M_HELP_ABOUT 300

static const char* menulist[MAX_MENU_ITEMS][MAX_SUB_ITEMS];

CDKMENU* makeMenu(CDKSCREEN* cdkscreen);

#endif

