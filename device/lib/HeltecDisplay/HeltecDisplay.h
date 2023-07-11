#ifndef LIB_HELTEC_DISPLAY
#define LIB_HELTEC_DISPLAY

#include <Wire.h>  
#include "HT_SSD1306Wire.h"

void init_display();
void display_message(String message);

#endif