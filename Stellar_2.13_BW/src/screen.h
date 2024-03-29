#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH				256
#define SCREEN_HEIGHT				128

#define SCREEN_NUM_GREYS			5
#define SCREEN_FIRST_GREY_IDX		0
#define SCREEN_EXTRA_COLOR_INDEX	-1 		//set to negative if nonexistent 5
#define SCREEN_TX_BPP				1		//in transit 4

#define SCREEN_WIDTH_MM				48
#define SCREEN_HEIGHT_MM			24

#define SCREEN_BYTE_FILL			0x44	//white

#define SCREEN_TYPE					TagScreenEink_BW_1bpp //TagScreenEink_BWR_6colors

#define SCREEN_DATA_PASSES			2

#endif
