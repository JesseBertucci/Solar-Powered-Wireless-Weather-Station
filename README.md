# Solar-Powered-Wireless-Weather-Station

Solar-Powered Wireless Weather Station, can either report weather data via a web server or an IoT service such as Blynk. I will include source code files for both options.

This Weather Station is designed to run completely off-grid, on battery and solar power alone. Normally, the ESP32 is in 'deep sleep', running only on its ULP co-processor core. Every ten minutes, the ULP core wakes the two high performance processor cores, the high performance cores connect to wifi and either setup a web server or connect to the Blynk IoT cloud (your choice depending on which source code file you use). Once the connection is established, the ESP32 takes tempurature, pressure, and humidity readings from the BME280. It also takes voltage readings to determine the battery level. All this information is accessible via web server or Blynk. 

This project requires the following:
1. ESP32 Microprocessor
2. BME280 Tempurature, Humidity, Pressure, and Altitude Sensor
3. 18650 Battery
4. 18650 Battery tray
5. 100uF Capacitor 
6. 2x 100Kohm resistor
7. TP4056 Lithium Battery Charger Module
8. 6V 3W Solar Panel

