#include <Arduino.h>
#include <SmartGardenComms.h>
#include <HeltecDisplay.h>
#include <FlowSensor.h>

float total_litres;
int last_tx_no;
int reading_index;

float stored_reading_nm[MAX_READINGS] = {0};
float stored_reading_om[MAX_READINGS] = {0};
void setup() 
{
  total_litres = 0.0;
  last_tx_no = 0;

  reading_index = 0;

  Serial.begin(115200);
  lora_init_receiver();
  init_display();
  connect_to_wifi();

  display_message("Ready!");

}

String rx;
float current_liters_nm, current_liters_om;

int package_diff;
float nm_avg, om_avg;

void house_work(flow_measurement fm)
{
  current_liters_nm = fm.new_membrane_flow / 60.0;
  current_liters_om = fm.old_membrane_flow / 60.0;

  total_litres += (current_liters_nm + current_liters_om);

  package_diff = fm.tx_number - last_tx_no;

  if (package_diff == 1)
  {
    stored_reading_nm[reading_index] = current_liters_nm;
    stored_reading_om[reading_index] = current_liters_om;

    Serial.print("Stored nm: ");
    Serial.println(stored_reading_nm[reading_index]);

    reading_index++;
  }
  else if (package_diff > 1)
  {
    for (int i = 0; i < package_diff; i++)
    {
      stored_reading_nm[reading_index + i] = current_liters_nm;
      stored_reading_om[reading_index + i] = current_liters_om;
    }

    reading_index += package_diff;
  }
  else if (package_diff < 0)
  {
    last_tx_no = fm.tx_number - 1;
    reading_index = 0;


    nm_avg = om_avg = 0;
    for (int i = 0; i < MAX_READINGS; i++)
    {
      nm_avg += stored_reading_nm[i];
      om_avg += stored_reading_om[i];
    }

    post_data(nm_avg, om_avg);

    Serial.print("Posted nm liters: ");
    Serial.println(nm_avg * 1.0 / MAX_READINGS);

    Serial.print("Posted om liters: ");
    Serial.println(om_avg * 1.0 / MAX_READINGS);
    
    float stored_reading_nm[MAX_READINGS] = {0};
    float stored_reading_om[MAX_READINGS] = {0};
  }
}

flow_measurement fm;
void loop() {
  // put your main code here, to run repeatedly:
  lora_receive_reading(fm);

  if (fm.new_membrane_flow > 0 || fm.old_membrane_flow > 0)
  {
    house_work(fm);

    last_tx_no = fm.tx_number;

    display_message("New membrane flow: " + String(fm.new_membrane_flow) + " L/min");
    display_message("Old membrane flow: " + String(fm.old_membrane_flow) + " L/min", 0, 12);
    display_message("Tx No: " + String(fm.tx_number), 0, 24);
    display_message("Total litres: " + String(total_litres), 0, 36);

    clear_display();
 }

  fm.new_membrane_flow = fm.old_membrane_flow = current_liters_nm = current_liters_om = 0;
}
