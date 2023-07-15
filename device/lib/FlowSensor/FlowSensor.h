#ifndef LIB_FLOW
#define LIB_FLOW

#define SENSOR 7
#define CALIBRATION_FACTOR 4.5
#define INTERVAL 1000
#define FLOW_TO_TOTAL_LITRES

void init_flow_sensor();
int measure_flow();
int calculate_litre_output(int flow);

#endif