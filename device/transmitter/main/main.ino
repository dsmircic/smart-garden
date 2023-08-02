#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

uint8_t packet_no;

void setup()
{
  Serial.begin(115200);
  lora_init_transmitter();
  init_display();
  init_flow_sensor();

  packet_no = 0;
}

flow_measurement fm;
void loop() 
{
  measure_flow(fm, true);

  if (fm.flow > 0)
  {
    fm.tx_number = packet_no;
    packet_no++;

    lora_send_reading(fm);

    display_message("Flow: " + String(fm.flow) + " L/min", 0, 0);
    display_message("Tx No: " + String(fm.tx_number), 0, 40);

    if (packet_no == 100)
      packet_no = 0;

    clear_display();
  }

  fm.flow = 0;

}