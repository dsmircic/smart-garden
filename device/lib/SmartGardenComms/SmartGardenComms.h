#ifndef LIB_LORA
#define LIB_LORA

#include "LoRaWan_APP.h"
#include <ArduinoJson.h>
#include <FlowSensor.h>

#include <WiFi.h>
#include <HTTPClient.h>

#include "config.h"

#pragma region LoRa
/**
 * @brief Initializes transmitter for LoRa communication.
 * 
 */
void lora_init_transmitter();

/**
 * @brief Initializes receiver for LoRa communication.
 * 
 */
void lora_init_receiver();

/**
 * @brief Sends LoRa message to the receiver on the specified frequency.
 * 
 * @param fm reading to be sent.
 */
void lora_send_reading(flow_measurement fm);

/**
 * @brief Receives LoRa packet.
 * 
 * @param fm flow_measurement struct to store the received data
 * @return 1 if message is consumption, 0 otherwise
 */
int lora_receive_reading(flow_measurement &fm);


void OnTxDone( void );
void OnTxTimeout( void );

/**
 * @brief Callback funciton for receiveing packets.
 * 
 * @param payload received message
 * @param size packet size
 * @param rssi signal strength
 * @param snr 
 */
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );
#pragma endregion

#pragma region HTTP

/**
 * @brief Posts data to the HTTP server.
 * 
 * @param v Volume parameter to be posted.
 */

#pragma endregion 

#pragma region WiFi

/**
 * @brief Connects to the network specified in config.h.
 * 
 */
void connect_to_wifi();
#pragma endregion

#endif