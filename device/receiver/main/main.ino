#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

unsigned long total_litres;
uint8_t last_tx_no;
uint8_t reading_index;
float unpublished_volume;

float stored_reading[MAX_READINGS] = {0};
void setup()
{
  total_litres = 0;
  last_tx_no = 0;

  reading_index = 0;
  unpublished_volume = 0.0;

  Serial.begin(115200);
  lora_init_receiver();
  init_display();
  connect_to_wifi();

  display_message("Ready!");

}

String rx;
float current_liters;

int package_diff;
float sum;

void house_work(flow_measurement fm)
{
  current_liters = fm.flow / 60.0;

  package_diff = fm.tx_number - last_tx_no;

  if (package_diff == 1)
  {
    stored_reading[reading_index] = current_liters;

    reading_index++;
  }
  else if (package_diff > 1)
  {
    for (int i = 0; i < package_diff; i++)
    {
      stored_reading[reading_index + i] = current_liters;
    }

    reading_index += package_diff;
  }
  else if (package_diff < 0)
  {
    last_tx_no = fm.tx_number - 1;
    reading_index = 0;

    sum = 0;
    for (int i = 0; i < MAX_READINGS; i++)
    {
      sum += stored_reading[i];
    }

    int response = post_data(sum + unpublished_volume);

    if (response != HTTP_CODE_OK)
    {
      unpublished_volume += sum;
    }
    else
    {
      unpublished_volume = 0.0;
    }

    total_litres += sum;
    
    float stored_reading[MAX_READINGS] = {0};
  }
}

flow_measurement fm;
void loop() {
  // put your main code here, to run repeatedly:

  if (!is_wifi_connected())
    connect_to_wifi();

  lora_receive_reading(fm);

  if (fm.flow > 0)
  {
    house_work(fm);

    last_tx_no = fm.tx_number;

    display_message("Flow: " + String(fm.flow) + " L/min");
    display_message("Tx No: " + String(fm.tx_number), 0, 12);
    display_message("Total litres: " + String(total_litres), 0, 24);

    clear_display();
 }

  fm.flow = current_liters = 0;
}
