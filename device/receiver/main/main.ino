#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>

void setup() {
  Serial.begin(115200);
  lora_init_receiver();
  init_display();

}

String rx;
void loop() {
  // put your main code here, to run repeatedly:
  rx = lora_receive_message();

  if (rx != NULL)
    display_message("Recv: " + rx);
}
