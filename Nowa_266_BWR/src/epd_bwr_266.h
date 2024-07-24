#pragma once

uint8_t EPD_BWR_266_detect(void);
uint8_t EPD_BWR_266_read_temp(void);

uint8_t EPD_BWR_266_Display_start(uint8_t full_or_partial);
void EPD_BWR_266_Display_byte(uint8_t data);
void EPD_BWR_266_Display_buffer(unsigned char *image, int size);
void EPD_BWR_266_Display_end();
void EPD_BWR_266_Display_color_change();


uint8_t EPD_BWR_266_Display(unsigned char *image, int size, uint8_t full_or_partial);
void EPD_BWR_266_set_sleep(void);



