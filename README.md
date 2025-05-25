🌱 IoT-Based Smart Hydroponics Monitoring System
This project is an IoT-enabled Smart Hydroponics System built using the ESP32 microcontroller. It continuously monitors water level, temperature, humidity, and TDS (Total Dissolved Solids) to ensure an optimal growing environment for hydroponic plants. Real-time sensor data is displayed on the Blynk IoT platform, and alerts are sent when parameters go out of the optimal range.

🚀 Features
🌡️ Temperature & Humidity Monitoring using DHT11 sensor
💧 Water Level Detection using Ultrasonic Sensor
🧪 TDS Measurement using an analog TDS sensor
⚙️ Automatic Nutrient Control through a relay-controlled pump based on TDS level
📱 Real-Time Data Visualization via the Blynk mobile app
🔔 Instant Alerts & Notifications for abnormal water level, TDS, temperature, and humidity
⚡ Built with ESP32 for WiFi connectivity and processing power

🛠️ Hardware Components
ESP32 Development Board
DHT11 Temperature & Humidity Sensor
Ultrasonic Sensor (HC-SR04)
TDS Sensor
Relay Module
Water/Nutrient Pump
Wires, Breadboard, Power Supply

⚙️ Functional Workflow
1)ESP32 connects to WiFi and initializes all sensors.
2)Water Level is measured using an ultrasonic sensor, and alerts are sent if the level is too high or too low.
3)TDS Value is monitored. If it's below the threshold, a relay triggers the nutrient pump to balance it.
4)Temperature and Humidity readings are checked against ideal ranges, with alerts pushed via Blynk if needed.
5)All data is sent to Blynk, where it can be viewed in real-time on a mobile dashboard.


