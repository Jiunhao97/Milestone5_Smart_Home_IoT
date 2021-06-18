# **Milestone5_Smart_Home_IoT**<br />

## **(1) Software/Tools Setup**<br />
Software/Tools required: [Arduino IDE](https://www.arduino.cc/en/software)<br />
![alt text](https://github.com/Jiunhao97/screenshot/blob/main/Screenshot%202021-06-18%20194923.jpg)<br />

## **(2) Configuration Steps**<br />
To ease the development of this work, *Arduino IDE* which is pretty simple and powerful with serial monitor feature will be used.<br />

As *Arduino IDE* is not compatible for programming of STM32 Nucleo Boards by default, these configuration steps are necessary to perform in Arduino IDE to make it compatible for programming of STM32 Nucleo Boards:<br />

   1. Open **Arduino IDE**
   2.	Go to _**File**_ -> _**Preferences**_
   3.	In _**Additional Boards Manager URLs**_ column, type: https://github.com/stm32duino/BoardManagerFiles/raw/master/package_stmicroelectronics_index.json
   4.	Click _**OK**_
   5.	Go to _**Tools**_ -> _**Board**_ -> _**Boards Manager**_
   6.	In _**search**_ column, search for “STM32”, click on “STM32 MCU based boards by STMicroelectronics” to install the board package. All the series of STM32 board by STMicroelectronics will be installed in Arduino IDE.
   7.	Go to _**Tools**_ -> _**Board**_, choose for your STM32 board series. In this work, **Nucleo-64** will be used.
   8.	Go to _**Tools**_ -> _**Board part number**_, choose for your STM32 board part number. In this work, **Nucleo F446RE** will be used.
   9.	Go to _**Tools**_ -> _**Port**_ and select the port on which your STM32 board is connected to.<br />
 
## **(3) Steps for Firmware Development**<br />
The firmware development can be classified into 4 sections, which are:<br />
 
### **3.1 Define sensor library**<br />
Some of the sensors available in the market required additional library provided by the sensor manufacturer to configure the sensor so that it can operate properly. Hence, it is mandatory to define the sensors’ library at the beginning of code.<br />

Sensor that required additional library: **DHT11**<br />

__Additional library required__: *DHT.h* (download from: _**Arduino IDE**_ -> _**Sketch**_ -> _**Include Library**_ -> _**Manage Libraries**_ -> search for “DHT sensor library by Adafruit” and click to download)<br />

```C++
//Part 1 Define sensor library
#include <DHT.h>
```

### **3.2 Define pin connection of sensor & variable**<br />
The **pin number** in which the sensors are connected to are required to be defined in this section so that the program know which port should the signal receive from/send to.<br />

Also, the **variables** to be used in the program should be defined in this section too.<br />

```C++
//Part 2 Define pin connection & variable
int TemperatureSensor=A0;
float analogTemperature;

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
float Humidity;

int GasSensor=A1;
int GasLED=3;
float GasSensorValue;

int PIRSensor=8;
int PIRLED=4;
int PIRState=LOW;

int DoorSensor=13;
int DoorLED=7;
int DoorState=LOW;
```

### **3.3 Initialize the board**<br />

