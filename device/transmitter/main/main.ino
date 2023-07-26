#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

int packet_no;

void setup()
{
  Serial.begin(115200);
  lora_init_transmitter();
  init_display();
  init_flow_sensor();

  packet_no = 1;

  display_message("Ready!");
}

flow_measurement fm;
void loop() 
{
  measure_flow(fm);

  if (fm.new_membrane_flow > 0 || fm.old_membrane_flow > 0)
  {
    fm.tx_number = packet_no;
    packet_no++;

    lora_send_reading(fm);

    display_message("Clear flow: " + String(fm.new_membrane_flow) + " L/min", 0, 0);
    display_message("Waste flow: " + String(fm.old_membrane_flow) + " L/min", 0, 20);
    display_message("Tx No: " + String(fm.tx_number), 0, 40);

    clear_display();

    if (packet_no >= MAX_READINGS)
      packet_no = 1;

  }

  fm.new_membrane_flow = fm.old_membrane_flow = 0;

}
