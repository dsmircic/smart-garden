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

flow_measurements fm;
void loop() 
{
  measure_flow(fm);



  if (fm.clear_flow > 0 || fm.waste_flow > 0)
  {
    // lora_send_message(String(flow));
    display_message("Clear flow: " + String(fm.clear_flow) + " L/min", 0, 0);
    display_message("Waste flow: " + String(fm.waste_flow) + " L/min", 0, 20);

    clear_display();
  }


}
