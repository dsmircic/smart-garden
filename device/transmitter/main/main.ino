#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  lora_init_transmitter();
  init_display();

}

String message = "penis";
void loop() 
{
  // put your main code here, to run repeatedly:
  lora_send_message(message);
  display_message("Sent: " + message);

  delay(1000);

}
