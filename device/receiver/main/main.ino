#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include "help.h"

int total_litres;
void setup() 
{
  total_litres = 0;

  Serial.begin(115200);
  lora_init_receiver();
  init_display();

}

String rx;
void loop() {
  // put your main code here, to run repeatedly:
  rx = lora_receive_message();

  if (rx != NULL)
  {
    display_message("Current flow: " + rx + " L/min");
    calculate_litre_output(rx.toInt());
  }
}
