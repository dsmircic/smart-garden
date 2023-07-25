#ifndef CONFIG_H
#define CONFIG_H

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

#define WIFI_SSID       "MaslinskiDvori"
#define WIFI_PASS       "4455667788"

#define HTTP_URL        "https://data-gateway.akenza.io/v3/capture?secret="
#define HTTP_SECRET     "59vpqpithrugcnqjpawbbuq62sb9n8pm"
#define DEVICE_ID       "B6DA1CD53E73C618"
#define HTTP_TOPIC      "default"

#endif // CONFIG_H
