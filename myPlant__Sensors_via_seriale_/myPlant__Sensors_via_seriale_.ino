/*  PROGETTO "myPlant" 
    by ZIRCONET (2016)

    Sketch per test sensori di umidità e temperatura aria e umidità terreno
    print via seriale

    MOISTURE SENSOR collegato a 3,3V + GND + porta analogica A0
    DHT11 collegato a 5V + GND + porta digitale 8

*/

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 8  //DHT11 SENSORS pin declaration


int sensorPin = A0;    // MOISTURE SENSOR analog input 
int sensorValue = 0;   // declaration sensor value
int acquaBarrier = 150;
int sensorLed = 13;    // LED input



void setup() {
  Serial.begin(9600);
  Serial.println("myPlant Project   ----->   by Zirconet (2016)");
  Serial.println();
  Serial.println("Connecting to serial...");
  pinMode(sensorPin, INPUT);
  pinMode(sensorLed, OUTPUT);
}

void loop() {
  digitalWrite(sensorLed, HIGH); 
  sensorValue = analogRead(sensorPin);
  Serial.print("Umidita' Terreno rilevata = ");
  Serial.print(sensorValue);
  if (sensorValue <=acquaBarrier) {
    Serial.println("     VALORE IRRIGAZIONE OK");
    }else{
    Serial.println("     ATTENZIONE SERVE IRRIGAZIONE");   
    }

  int chk;
  chk = DHT.read(DHT11_PIN); //read data from DHT11 sensor
  switch (chk) {
    case DHTLIB_OK:
              Serial.print("");
              break;
    case DHTLIB_ERROR_CHECKSUM:
              Serial.print("DHT sensor Checksum error, \t");
              break;
    case DHTLIB_ERROR_TIMEOUT:
              Serial.print("DHT sensor Timeout error, \t");
              break; 
    default:
              Serial.print("DHT sensor Unknow Error, \t");
              break;
    }
  //DISPLAY DATA FROM DHT11
  Serial.print("Umidità aria = ");
  Serial.print(DHT.humidity,1);
  Serial.print("%");
  Serial.print(",\t");
  Serial.print("Temperatura aria = ");
  Serial.print(DHT.temperature,1);
  Serial.println("°");
  Serial.println();
  digitalWrite(sensorLed, LOW);
  delay (5000);
}
