#ifndef LIB_FLOW
#define LIB_FLOW

#include <Arduino.h>
#include <cmath>

#define SENSOR 7
#define CALIBRATION_FACTOR 7.5
#define INTERVAL 1000

/**
 * @brief Stores clear water flow in liters/min and packet number as integer.
 * 
 */
struct flow_measurement
{
    float flow;
    int tx_number;
};

/**
 * @brief Initializes sensor for measuring water flow on both the clear and waste water outlets.
 * 
 */
void init_flow_sensor();

/**
 * @brief Measures clear and waste water flow in liters/min.
 * 
 * @param fm water flow measurements.
 */
void measure_flow(flow_measurement &fm);

#endif