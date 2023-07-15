#include "FlowSensor.h"

long current_millis, previous_millis;

volatile byte pulse_count;
byte pulse_1_sec;

float flow_rate;

void IRAM_ATTR pulse_counter()
{
  pulse_count++;
}

void init_flow_sensor()
{
    pinMode(SENSOR, INPUT_PULLUP);

    pulse_count = 0;
    pulse_1_sec = 0;
    flow_rate = 0.0;

    current_millis = 0;
    previous_millis = 0;

    attachInterrupt(digitalPinToInterrupt(SENSOR), pulse_counter, FALLING);
}


int measure_flow()
{
    current_millis = millis();
    if (current_millis - previous_millis > INTERVAL)
    {
        pulse_1_sec = pulse_count;
        pulse_count = 0;

        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.
        flow_rate = ((1000.0 / (millis() - previous_millis)) * pulse_1_sec) / CALIBRATION_FACTOR;
        previous_millis = millis();

        // Divide the flow rate in litres/minute by 60 to determine how many litres have
        // passed through the sensor in this 1 second interval, then multiply by 1000 to
        // convert to millilitres.

        // Add the millilitres passed in this second to the cumulative total
        
        // Print the flow rate for this second in litres / minute
        Serial.print("Flow rate: ");
        Serial.print(int(flow_rate));  // Print the integer part of the variable
        Serial.println("L/min");

        return flow_rate;
    }

    return -1;
}