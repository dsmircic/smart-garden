## Prerequisites
- Arduino IDE [https://www.arduino.cc/en/software]
- Windows USB CP210x Driver [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads]

#### 1. Clone the repository with:
```git
git clone https://github.com/dsmircic/smart-garden
```

#### 2. Open the sketch with ARDUINO IDE.
```
File -> Open -> device/transmitter/main.ino
File -> Open -> device/receiver/main.ino
```

#### 3. Download the necessary libraries for the esp32 Heltec board
```
1. Download Heltec Board dependencies [https://docs.heltec.org/en/node/esp32/quick_start.html#via-arduino-board-manager]
2. Restart IDE
3. Install Heltec ESP32 Dev-Series Library **VERSION 0.0.7**
```

#### 4. Move libraries to required folder
```
Open File -> Preferences and copy _Sketchbook location_ (Usually _C://user/Documents_)
Go to _Sketchbook location_ -> Libraries and copy the contents of the git repo device/libraries
```

#### 5. Upload the code to Heltec Board and run the code

#### 6. Links
https://github.com/HelTecAutomation/CubeCell-Arduino/releases/download/V1.5.0/package_CubeCell_index.json
https://github.com/HelTecAutomation/CubeCell-Arduino/releases/tag/V1.5.0/package_CubeCell_index.json