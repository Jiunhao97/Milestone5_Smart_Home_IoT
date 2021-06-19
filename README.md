# **STM32-Based Smart Home System**<br />
# **Milestone 5: Work Procedure Documentation**<br />

## **(0) Group Details**<br />
MKEL1123-05: Advanved Microprocessor System (Sem 20202021-2)<br />

_**Lecturer**_: Prof. Madya Muhammad Mun’im Ahmad Zabidi<br />
_**Group Member**_ | _**Matric ID**_
------------ | ---------
Chng Tai Yau | MKE201094
Koh Jiun Hao | MKE201088
Poo Chee Ming | MKE201075

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
This section initializes the board with pin configurations and serial port enablement when the board is power up. It will only run for once in the whole power up cycle.<br />

```C++
//Part 3 Initialize the board
void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(GasLED,OUTPUT);

  pinMode(PIRSensor,INPUT);
  pinMode(PIRLED,OUTPUT);

  pinMode(DoorSensor,INPUT_PULLUP);
  pinMode(DoorLED,OUTPUT);
}
```

### **3.4 Main functional code**<br />
This section is the main functional code of the program where it will keep on looping as long as the board is still power up. The main functional code includes receive data from sensors, and send output to receiver such as LED and buzzer.<br />

The algorithm for this work is that the board will read in data from temperature sensor, humidity sensor and gas sensor every 5 seconds. While for motion detection and door state detection, the board will always read in data from PIR sensor and contact switch to give reaction immediately when signals are detected.<br />

#### *Coding for temperature sensor:*<br />
```C++
float val = analogRead(TemperatureSensor);
float mv = val*4.88;
analogTemperature = mv/10;

Serial.print("Temperature: ");
Serial.print(analogTemperature);
Serial.println(" C");
```

#### *Coding for humidity sensor:*<br />
```C++
Humidity = dht.readHumidity();

Serial.print("Humidity: ");
Serial.println(Humidity);
```

#### *Coding for gas sensor:*<br />
```C++
GasSensorValue = analogRead(GasSensor);
  
Serial.print("Gas Concentration: ");
Serial.println(GasSensorValue);
  
if(GasSensorValue > 250)
{
    Serial.println("! ! ! Smoke detected ! ! !");
    for (int count = 0; count < 20; count++)
    {
      digitalWrite(GasLED,HIGH);
      delay(300);
      digitalWrite(GasLED,LOW);
      delay(300);

      GasSensorValue = analogRead(GasSensor);
      if (GasSensorValue < 250)
      {
        break;
      }
    }
}
else
{
    digitalWrite(GasLED,LOW);
}
```

#### *Coding for PIR sensor and contact switch:*<br />
```C++
for (int count = 0; count < 50; count++)
{
    delay (100);
    
    PIRState = digitalRead(PIRSensor);
    if(PIRState == HIGH)
    {
      digitalWrite(PIRLED,HIGH);
      delay(5000); 
    }
    else
    {
      digitalWrite(PIRLED,LOW);
    }
  
    DoorState = digitalRead(DoorSensor);
    if (DoorState == HIGH)
    {
      for (int count = 0; count < 20; count++)
      {
        digitalWrite(DoorLED,HIGH);
        delay(300);
        digitalWrite(DoorLED,LOW);
        delay(300);
        
        DoorState = digitalRead(DoorSensor);
        if (DoorState == LOW)
        {
          break;
        }
      }
    }
    else
    {
      digitalWrite(DoorLED,LOW);
    }
}
```

*Click [here](https://github.com/Jiunhao97/Milestone5_Smart_Home_IoT/blob/main/stm32_iot_smart_home.ino) for complete source code.*<br />

## **(4) Steps for Hardware Development**<br />
Sensors used in this work and their pins connection to Nucleo F446RE board:<br />
 
### **4.1 LM35 Temperature Sensor**<br />

