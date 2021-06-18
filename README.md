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
   9.	Go to _**Tools**_ -> _**Port**_ and select the port on which your STM32 board is connected to.
