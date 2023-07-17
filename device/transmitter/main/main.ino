#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

float packet_no;

void setup()
{
  Serial.begin(115200);
  lora_init_transmitter();
  init_display();
  init_flow_sensor();

  packet_no = 0.0;
}

flow_measurement fm;
void loop() 
{
  measure_flow(fm);

  if (fm.clear_flow > 0 || fm.waste_flow > 0)
  {
    fm.tx_number = packet_no;
    packet_no += 0.01;

    lora_send_reading(fm);

    display_message("Clear flow: " + String(fm.clear_flow) + " L/min", 0, 0);
    display_message("Waste flow: " + String(fm.waste_flow) + " L/min", 0, 20);
    display_message("Tx No: " + String(fm.tx_number), 0, 40);

    clear_display();
  }

  fm.clear_flow = fm.waste_flow = 0;

}
