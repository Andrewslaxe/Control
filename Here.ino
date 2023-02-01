#include "DallasTemperature.h"
#include "OneWire.h"

// Data wire is plugged into pin 4 on the ESP32
#define ONE_WIRE_BUS 14
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

const int buttonPin = 32;
const int temperaturePin = 27;
int buttonState = 0;
float Temp[2]= {0,0};
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void) {
  pinMode(buttonPin, INPUT);
  pinMode(temperaturePin, OUTPUT);
  Serial.begin(115200);
  sensors.begin();
}

void loop(void) {
  sensors.requestTemperatures();
  if(buttonState != digitalRead(buttonPin)){
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      Serial.println("Button pressed");
      digitalWrite(temperaturePin, HIGH);
    }
    else{
      digitalWrite(temperaturePin, LOW);
      Serial.println("Not pressed");
    }
  }
  
  Temp[1]=sensors.getTempCByIndex(0);
  if(Temp[0] != Temp[1]){
    Serial.print("Temperature is: ");
    Serial.println(Temp[1]);
    Temp[0] = Temp[1];
  }

  delay(1000);
}