#ifndef LIB_LORA
#define LIB_LORA

// #include <LoRa.h>
// #include <SPI.h>
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
 */
void lora_receive_reading(flow_measurement &fm);


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

void post_data(float v1, float v2);

#pragma endregion 

#pragma region WiFi

void connect_to_wifi();
#pragma endregion

#endif