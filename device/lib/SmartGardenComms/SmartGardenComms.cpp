#include "SmartGardenComms.h"

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

  jsonDoc["cf"] = fm.clear_flow;
  jsonDoc["wf"] = fm.waste_flow;
  jsonDoc["tx"] = fm.tx_number;

  serializeJson(jsonDoc, txpacket);

  // sprintf(txpacket,"%s %0.2f", message, txNumber);  //start a package

  Serial.printf("\r\nsending packet \"%s\" , length %d\r\n", txpacket, strlen(txpacket));

  Radio.Send((uint8_t *)txpacket, strlen(txpacket)); // send the package out

  Radio.IrqProcess();
  Serial.println("Message sent!");
}

void lora_receive_reading(flow_measurement &fm)
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
      fm.clear_flow = jsonDoc["cf"].as<float>();
      fm.waste_flow = jsonDoc["wf"].as<float>();
      fm.tx_number = jsonDoc["tx"].as<double>();
    }
    else
    {
      fm.clear_flow = -1;
      fm.waste_flow = -1;
      fm.tx_number = -1;
    }

    // receivedMessage = String(rxpacket);
    rxSize = 0;
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

#pragma region MQTT

WiFiClient wifi_client;
Adafruit_MQTT_Client mqtt_client(&wifi_client, mqtt_broker, mqtt_port, mqtt_username, mqtt_password);

void publish_to_mqtt(float volume)
{
  // Convert the integer value to a string
  char payload[10];
  snprintf(payload, sizeof(payload), "%d", volume);

  // Publish the value to the MQTT topic
  if (mqtt_client.connected())
  {
    Serial.println("Publishing message to MQTT topic...");
    mqtt_client.publish(mqtt_topic, payload);
  }
  else
  {
    Serial.println("MQTT not connected, retrying...");
    connect_to_mqtt();
  }

  // Wait before sending the next update
  delay(5000); // Change this delay to the desired interval
}

void connect_to_mqtt()
{
  Serial.print("Connecting to MQTT broker...");
  while (!mqtt_client.connected())
  {
    if (mqtt_client.connect())
    {
      Serial.println("connected!");
    }
    else
    {
      Serial.print("failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

#pragma endregion

#pragma region WiFi

void connect_to_wifi()
{
  WiFi.begin(wifi_ssid, wifi_password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(wifi_ssid);
}

#pragma endregion