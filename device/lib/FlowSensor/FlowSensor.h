#ifndef LIB_FLOW
#define LIB_FLOW

#include <Arduino.h>

#define SENSOR 7
#define CALIBRATION_FACTOR 4.5
#define INTERVAL 1000

void init_flow_sensor();
int measure_flow();
void IRAM_ATTR pulse_counter();

#endif