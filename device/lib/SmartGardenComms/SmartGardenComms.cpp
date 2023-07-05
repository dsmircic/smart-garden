#include "SmartGardenComms.h"

void lora_init()
{
  // put the right pin numbers or -1 for default. On my TTGO it's 5, 19, 27, 18
  // SPI.begin(5, 19, 27, 18);

  // // on my TTGO it's 18, 14, 26
  // LoRa.setPins(18, 14, 26);
  // LoRa.setSPIFrequency(1E6);

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, 433E6 /*long BAND*/);

  // if (!LoRa.begin(LORA_FREQ))
  // {
  //   Serial.println("Starting LoRa failed!");
  //   while(1);

  // }

  Serial.println("Setup successful!");

}

void lora_send_message(String message)
{
  Serial.print("Sending packet: ");

  LoRa.beginPacket(false);
  Serial.print("1");
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  Serial.print("2");
  LoRa.print(message);
  Serial.print("3");
  LoRa.endPacket(false);

  Serial.print("Message sent!");
  
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(25, LOW);   
}