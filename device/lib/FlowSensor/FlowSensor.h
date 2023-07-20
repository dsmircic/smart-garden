#ifndef LIB_FLOW
#define LIB_FLOW

#include <Arduino.h>
#include <cmath>

#define C_SENSOR 7
#define W_SENSOR 19
#define CALIBRATION_FACTOR 7.5
#define INTERVAL 1000

/**
 * @brief Stores clear and waste water flow in liters/min.
 * 
 */
struct flow_measurement
{
    float clear_flow;
    float waste_flow;
    double tx_number;
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
void measure_flow(flow_measurement &fm);

#endif