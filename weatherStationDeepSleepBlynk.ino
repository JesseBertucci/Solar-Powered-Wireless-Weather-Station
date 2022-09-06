#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLXxX2nj3Y" // replace this with template id
#define BLYNK_DEVICE_NAME "Wireless Weather Station" // replace this with your device name

#include <WiFi.h> // importing all the required libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

float temperature; // parameters
float humidity;
float pressure;
float batteryLevel;
#define SEALEVELPRESSURE_HPA (1013.25)

#define VBAT_PIN 35       // battery level measurement pin
#define BATTV_MAX 4.1     // maximum voltage of battery
#define BATTV_MIN 3.2     // what we regard as an empty battery
#define BATTV_LOW 3.4     // voltage considered to be low battery

Adafruit_BME280 bme;

char auth[] = "-QEQT8ErhjYXtPxxlOUT98HHSpleaiQg"; // replace this with your auth token
char ssid[] = "hive24"; // replace this with your wifi name (SSID)
char pass[] = "gS120Vu$"; // replace this with your wifi password

BlynkTimer timer;

#define DEEP_SLEEP_TIME 10 // determines the amount of time ESP32 will sleep between measurements

// deep sleep function
void goToSleep(){ 

  esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME * 60 * 1000000);
  esp_deep_sleep_start();  

}

float batteryPower(){ // battery level calculation function

  int analogReading = 0;

  analogReading = analogRead(VBAT_PIN);

  
  int battv = (analogReading / 4095) * 3.3 * 2 * 0.6227;  // last value '0.6227' is dependant on your system, change it until voltage displayed equals voltage read from multimeter
  int battpc = (uint8_t)(((battv - BATTV_MIN) / (BATTV_MAX - BATTV_MIN)) * 100); // calculates battery % 

/*
  Serial.println("Analog Reading: ");   // removed comments for debugging
  Serial.println(analogReading);
  Serial.println("battv: ");
  Serial.println(battv);
  Serial.println("battpc: ");
  Serial.println(battpc);
*/

  return battpc;
}

void sendSensor(){
  
  temperature = bme.readTemperature();  // get sensor readings
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  batteryLevel = batteryPower();

/*
  if (isnan(humidity) || isnan(temperature) || isnan(pressure)){       // uncomment for debugging
    Serial.println("Failed to read from BME280 sensor!");
  }

  Serial.println("Tempurature: ");
  Serial.println(temperature);
  Serial.println("Humidity: ");
  Serial.println(humidity);
  Serial.println("Pressure: ");
  Serial.println(pressure);
  Serial.println("Battery Voltage: ");
  Serial.println(battv);
  Serial.println("Battery Power: ");
  Serial.println(battpc);
*/

  Blynk.virtualWrite(V0, temperature); // send all the values to their respective virtual pins
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, batteryLevel);

}

void setup(){
  
  //Serial.begin(115200);

  pinMode(VBAT_PIN, INPUT);

  bme.begin(0x76);   

  Blynk.begin(auth, ssid, pass);
  delay(1000);

  Blynk.run();

  for(int i = 0; i < 4; i++){
    sendSensor();
    delay(1000);
  }

  goToSleep();
}

void loop(){
  // No code here as deep sleep function re-run the setup() function when it wakes thus never entering this loop function
}