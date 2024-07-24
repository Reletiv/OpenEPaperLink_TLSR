#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH				304//184
#define SCREEN_HEIGHT				400//384

#define SCREEN_NUM_GREYS			5
#define SCREEN_FIRST_GREY_IDX		0
#define SCREEN_EXTRA_COLOR_INDEX	5		//set to negative if nonexistent
#define SCREEN_TX_BPP				4		//in transit

#define SCREEN_WIDTH_MM				29
#define SCREEN_HEIGHT_MM			67

#define SCREEN_BYTE_FILL			0x44	//white

#define SCREEN_TYPE					TagScreenEink_BWR_2bpp//TagScreenEink_BWR_6colors

#define SCREEN_DATA_PASSES			2

#endif
