## DEVICE
- devices used in this project:
  - 2 $\times$ ESP32 WiFi LoRa (V3) [https://heltec.org/project/wifi-lora-32-v3/]
  - 2 $\times$ YF-B7 Water Flow Sensor [https://media.digikey.com/pdf/data%20sheets/seeed%20technology/114991177_web.pdf]

One microcontroller is set up to read water flow data every second and transmit the data in the form of a JSON String through the LoRa protocol, the other is set up to receive LoRa data and post it to the ThingsBoard platform.

The transmitting microcontroller is measuring clear water flow and waste water flow at the output of a reverse osmosis desalinator. The flow is measured in L/MIN and is being sent to the receiver. The receiving end can then calculate the total volume which has passed throught the pipe.

Both microcontrollers have an external power source and are constantnly operational.
