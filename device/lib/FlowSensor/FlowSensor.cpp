#include "FlowSensor.h"

long current_millis, previous_millis;

volatile byte pulse_count_clear, pulse_count_waste;
byte pulse_1_sec_clear, pulse_1_sec_waste;

void IRAM_ATTR pulse_counter_clear()
{
  pulse_count_clear++;
}

void IRAM_ATTR pulse_counter_waste()
{
  pulse_count_waste++;
}

void init_flow_sensor()
{
    pinMode(C_SENSOR, INPUT_PULLUP);
    pinMode(W_SENSOR, INPUT_PULLUP);

    pulse_count_clear = 0;
    pulse_count_waste = 0;

    pulse_1_sec_clear = 0;
    pulse_1_sec_waste = 0;

    current_millis = 0;
    previous_millis = 0;

    attachInterrupt(digitalPinToInterrupt(W_SENSOR), pulse_counter_waste, FALLING);
    attachInterrupt(digitalPinToInterrupt(C_SENSOR), pulse_counter_clear, FALLING);
}


void measure_flow(flow_measurements &fm)
{
    current_millis = millis();
    if (current_millis - previous_millis > INTERVAL)
    {
        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.

        pulse_1_sec_clear = pulse_count_clear;
        pulse_count_clear = 0;
        fm.clear_flow = ((1000.0 / (millis() - previous_millis)) * pulse_1_sec_clear) / CALIBRATION_FACTOR;

        pulse_1_sec_waste = pulse_count_waste;
        pulse_count_waste = 0;
        fm.waste_flow = ((1000.0 / (millis() - previous_millis)) * pulse_1_sec_waste) / CALIBRATION_FACTOR;

        previous_millis = millis();

        // Divide the flow rate in litres/minute by 60 to determine how many litres have
        // passed through the sensor in this 1 second interval, then multiply by 1000 to
        // convert to millilitres.

        // Add the millilitres passed in this second to the cumulative total
        
        // Print the flow rate for this second in litres / minute

    }
}