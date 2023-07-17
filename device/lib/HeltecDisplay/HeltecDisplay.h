#ifndef LIB_HELTEC_DISPLAY
#define LIB_HELTEC_DISPLAY

#include <Wire.h>  
#include "HT_SSD1306Wire.h"

/**
 * @brief Initializes ESP32 Heltec LoRa/Wifi V3 display.
 * 
 */
void init_display();

/**
 * @brief Displays message on the touchscreen.
 * 
 * @param message message to be displayed
 * @param width X coordinate for message display
 * @param height Y coordinate for message display.
 */
void display_message(String message, int width = 0, int height = 0);

/**
 * @brief Clears the display from all data.
 * 
 */
void clear_display();

#endif