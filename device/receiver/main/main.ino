#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

float total_litres;
void setup() 
{
  total_litres = 0;

  Serial.begin(115200);
  lora_init_receiver();
  init_display();
  connect_to_wifi();

}

String rx;
flow_measurement fm;
void loop() {
  // put your main code here, to run repeatedly:
  lora_receive_reading(fm);

  if (fm.clear_flow > 0 || fm.waste_flow > 0)
  {
    total_litres += fm.clear_flow / 60;

    display_message("Clear flow: " + String(fm.clear_flow) + " L/min");
    display_message("Waste flow: " + String(fm.waste_flow) + " L/min", 0, 12);
    display_message("Tx No: " + String(fm.tx_number), 0, 24);
    display_message("Total litres: " + String(total_litres), 0, 36);

    clear_display();
  }

  post_data(100 / 60.0);
  fm.clear_flow = fm.waste_flow = 0;

  delay(10000);
}
