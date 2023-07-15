#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  lora_init_transmitter();
  init_display();
  init_flow_sensor();

}


void loop() 
{
  int flow = measure_flow();
  if (flow > 0)
  {
    lora_send_message(String(flow));
    display_message("Flow: " + String(flow) + " L/min");
  }

}
