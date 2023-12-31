#include "SmartGardenComms.h"
#include "config.h"

#pragma region LoRa

char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];

static RadioEvents_t RadioEvents;
int16_t rssi, rxSize;

void lora_init_transmitter()
{
  Mcu.begin();

  RadioEvents.TxTimeout = OnTxTimeout;

  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

  Serial.println("Transmitter setup successful!");
}

void lora_init_receiver()
{
  Mcu.begin();

  rssi = 0;

  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                    LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                    LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                    0, true, 0, 0, LORA_IQ_INVERSION_ON, true);
  Serial.println("Receiver setup successful!");
}

void lora_send_reading(flow_measurement fm)
{

  StaticJsonDocument<BUFFER_SIZE> jsonDoc;

  jsonDoc["cf"] = fm.flow;
  jsonDoc["ty"] = fm.type;
  jsonDoc["tx"] = fm.tx_number;

  serializeJson(jsonDoc, txpacket);

  // sprintf(txpacket,"%s %0.2f", message, txNumber);  //start a package

  Serial.printf("\r\nsending packet \"%s\" , length %d\r\n", txpacket, strlen(txpacket));

  Radio.Send((uint8_t *)txpacket, strlen(txpacket)); // send the package out

  Radio.IrqProcess();
  Serial.println("Message sent!");
}

int lora_receive_reading(flow_measurement &fm)
{
  String receivedMessage = "";
  StaticJsonDocument<BUFFER_SIZE> jsonDoc;
  Radio.Rx(0);

  Radio.IrqProcess();

  if (rxSize > 0)
  {
    DeserializationError error = deserializeJson(jsonDoc, rxpacket);

    if (!error)
    {
      fm.flow = jsonDoc["cf"].as<float>();
      fm.tx_number = jsonDoc["tx"].as<uint8_t>();
      fm.type = jsonDoc["ty"].as<uint8_t>();
    }
    else
    {
      fm.flow = -1;
      fm.tx_number = -1;
      fm.type = -1;
    }
    
    rxSize = 0;

    if (fm.type == 1)
      return 1;
  
    return 0;

  }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  rssi = rssi;
  rxSize = size;
  memcpy(rxpacket, payload, size);
  rxpacket[size] = '\0';
  Radio.Sleep();
  Serial.printf("\r\nreceived packet \"%s\" with rssi %d , length %d\r\n", rxpacket, rssi, rxSize);
}

void OnTxTimeout(void)
{
  Radio.Sleep();
  Serial.println("TX Timeout......");
}

#pragma endregion

#pragma region HTTP

HTTPClient http;
void post_data(float volume)
{
  // Convert float data to string
  String data = "{\"volume\":" + String(volume, 2) + "}";

  // Create the HTTP client

  // Set up the request URL with the secret and device ID
  String url = String(HTTP_URL) + String(HTTP_SECRET) + "&deviceId=" + String(DEVICE_ID) + "&topic=" + String(HTTP_TOPIC);

  // Make the HTTP POST request
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(data);

  // Check the response
  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  }
  else
  {
    Serial.print("Error in HTTP request. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }

  http.end();  // Free resources
}

#pragma endregion

#pragma region WiFi
void connect_to_wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
}

#pragma endregion