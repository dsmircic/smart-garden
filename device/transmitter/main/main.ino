#include <Arduino.h>
#include <SmartGardenComms.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  lora_init();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.println("Kita");
  lora_send_message("penis");

  delay(1000);

}
