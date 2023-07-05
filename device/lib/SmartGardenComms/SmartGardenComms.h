#ifndef LIB_LORA
#define LIB_LORA

// #include <LoRa.h>
// #include <SPI.h>
#include "heltec.h"

#define LORA_FREQ 866E6

void lora_init();
void lora_send_message(String message);

#endif