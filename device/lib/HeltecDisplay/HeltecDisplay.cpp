#include "HeltecDisplay.h"

SSD1306Wire  sg_display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED); // addr , freq , i2c group , resolution , rst

void init_display()
{
    sg_display.init();
    sg_display.clear();
    sg_display.display();
}

void display_message(String message, int width, int height)
{
    sg_display.drawString(width, height, message);
    sg_display.display();
}

void clear_display()
{
    sg_display.clear();
}