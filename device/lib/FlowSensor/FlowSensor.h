#ifndef LIB_FLOW
#define LIB_FLOW

#include <Arduino.h>

#define C_SENSOR 7
#define W_SENSOR 19
#define CALIBRATION_FACTOR 4.5
#define INTERVAL 1000

/**
 * @brief Stores clear and waste water flow in liters/min.
 * 
 */
struct flow_measurements
{
    float clear_flow;
    float waste_flow;
};

/**
 * @brief Initializes sensor for measuring water flow on both the clear and waste water outlets.
 * 
 */
void init_flow_sensor();

/**
 * @brief Measures clear and waste water flow in liters/min.
 * 
 * @param fm -> water flow measurements.
 */
void measure_flow(flow_measurements &fm);

#endif