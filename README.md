# ESP32 GPS-Speedo
En ESP32 based GPS Speedometer with 2 modes (made to measure the speed of my son's RC cars, but also perfectly good as a portable GPS/Speedometer)

I built this as a speedo to tape to my son's RC car (Rustler VXL) to measure speed and assist tuning, but it has all typical GPS and speedo functions too, selectable from a pushbutton on D27.


# Parts list
- a four pin 0.96 OLED module for the display connected via SDA/SCL 
- Neo 6M or 7M GPS module. I used a UBX2828/VK2828 all in one module from AliExpress
- An ESP32 module that exposes SDS/SCL and hardware serial RX/TX. I started with a ESP32 DevKit C, which worked fine - but as it needed to be portable I switched to a DFRobot Firebeetle ESP32-E (DFR0654) because of its embedded LiPo charging and battery management. 
- I'm running a tiny 801437 LiPo and it provides hours of use before needing a charge.


# Build decisions:
I used one of the two available embedded Serial hardware UARTS for the GPS I/O. In this case the second UART, pins 16/17 - RX2/TX2 so I wouldn't have issues uploading code (flashing uses RX/TX on pins 1 and 3 and it's likely a cause of a lot of "esptool won't upload" issues in forums when they are otherwise used). Of course you could assign software serial to other pins and change the code - but why wast perfectly good serial hardware UARTS) 

# Dependencies:
- SSD1306 Library from https://github.com/adafruit/Adafruit_SSD1306Uses
- TinyGPS++.h Library from https://github.com/mikalhart/TinyGPSPlus
- EasyButton library by Evert Arias from https://github.com/evert-arias/EasyButton

I'll add the STL files for the case to Thingyverse soon. I'm still prototyping.

![image](https://user-images.githubusercontent.com/44254504/161084981-3cd4a369-2f88-4bc7-9d31-ee61d21b9aa9.png)

![image](https://user-images.githubusercontent.com/44254504/161086058-b6a0f011-c273-465e-83b7-4b0232b52a0a.png)

![image](https://user-images.githubusercontent.com/44254504/161085339-df936c6c-519e-4767-8d74-5740f815928e.png)
