#include "FlowSensor.h"

long current_millis = 0;
long previous_millis = 0;

volatile byte pulse_count;
byte pulse1Sec = 0;

float flow_rate;
unsigned int flow_millilitres;
unsigned long total_litres;

void init_flow_sensor()
{
    pinMode(SENSOR, INPUT_PULLUP);

    pulse_count = 0;
    flow_rate = 0.0;
    flow_millilitres = 0;
    total_litres = 0;
    previous_millis = 0;

    attachInterrupt(SENSOR, pulse_counter, FALLING);
}

int measure_flow()
{
    current_millis = millis();
    if (current_millis - previous_millis > INTERVAL)
    {
        pulse1Sec = pulse_count;
        pulse_count = 0;

        // Because this loop may not complete in exactly 1 second intervals we calculate
        // the number of milliseconds that have passed since the last execution and use
        // that to scale the output. We also apply the calibrationFactor to scale the output
        // based on the number of pulses per second per units of measure (litres/minute in
        // this case) coming from the sensor.
        flow_rate = ((1000.0 / (millis() - previous_millis)) * pulse1Sec) / CALIBRATION_FACTOR;
        previous_millis = millis();

        // Divide the flow rate in litres/minute by 60 to determine how many litres have
        // passed through the sensor in this 1 second interval, then multiply by 1000 to
        // convert to millilitres.

        // Add the millilitres passed in this second to the cumulative total
        
        // Print the flow rate for this second in litres / minute
        Serial.print("Flow rate: ");
        Serial.print(int(flow_rate));  // Print the integer part of the variable
        Serial.print("L/min");
    }
}

int litres;
int calculate_litre_output(int flow)
{
    litres = flow / FLOW_TO_TOTAL_LITRES;
    total_litres += litres;

    Serial.print("Ouput Liquid Quantity: ");
    Serial.print(total_litres);
    Serial.println("L");

    return litres;
}