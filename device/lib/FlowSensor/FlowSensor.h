#ifndef LIB_FLOW
#define LIB_FLOW

#include <Arduino.h>

#define C_SENSOR 7
#define W_SENSOR 19
#define CALIBRATION_FACTOR 4.5
#define INTERVAL 1000

struct flow_measurements
{
    float clear_flow;
    float waste_flow;
};

void init_flow_sensor();
void measure_flow(flow_measurements &fm);

#endif