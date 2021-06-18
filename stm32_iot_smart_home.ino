//Part 1 Define sensor library
#include <DHT.h>



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



//Part 4
void loop() {
  float val = analogRead(TemperatureSensor);
  float mv = val*4.88;
  analogTemperature = mv/10;

  Serial.print("Temperature: ");
  Serial.print(analogTemperature);
  Serial.println(" C");


  
  Humidity = dht.readHumidity();

  Serial.print("Humidity: ");
  Serial.println(Humidity);


  
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
}
