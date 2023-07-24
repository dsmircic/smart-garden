#ifndef LIB_LORA
#define LIB_LORA

// #include <LoRa.h>
// #include <SPI.h>
#include "LoRaWan_APP.h"
#include <ArduinoJson.h>
#include <FlowSensor.h>

#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#pragma region LoRa
#define LORA_FREQ 868E6


#define RF_FREQUENCY                                915000000 // Hz

#define TX_OUTPUT_POWER                             14        // dBm

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       7         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         0         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_IQ_INVERSION_ON                        false


#define RX_TIMEOUT_VALUE                            1000
#define BUFFER_SIZE                                 64 // Define the payload size here

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

#pragma region MQTT
const char* mqtt_broker = "tcp://mqtt.akenza.io";
const int mqtt_port= 1883;
const char* mqtt_username = "07003fbc3ed0e204";
const char* mqtt_password = "awgacw9ac1g6jqbwxj5d30j2h5f968r9";
const char* mqtt_topic = "/up/awgacw9ac1g6jqbwxj5d30j2h5f968r9/id/B6DA2B2ECCDEF3AB";

void publish_to_mqtt(float volume);
void connect_to_mqtt();
#pragma endregion 

#pragma region WiFi
const char* wifi_ssid = "MaslinskiDvori";
const char* wifi_password = "4455667788";

void connect_to_wifi();
#pragma endregion

#endif