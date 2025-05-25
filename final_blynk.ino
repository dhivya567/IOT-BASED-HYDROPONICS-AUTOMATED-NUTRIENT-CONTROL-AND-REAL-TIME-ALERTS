#define BLYNK_TEMPLATE_ID "TMPL3fywnYzxV"
#define BLYNK_TEMPLATE_NAME "Hydroponics"
#define BLYNK_AUTH_TOKEN "Kw56P3_9XU076XcZ288JUVsIMWI3NyFG"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Blynk Authentication
char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials
char ssid[] = "OPPO A11k";
char pass[] = "dhivya03";

// Ultrasonic sensor pins
#define TRIG_PIN 5  
#define ECHO_PIN 18 

// DHT sensor pins
#define DHTPIN 14    
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

// TDS sensor pin and Relay pin
#define TdsSensorPin 34 
#define RelayPin_tds 21 

// Thresholds
const float WATER_LEVEL_MIN = 3.5;
const float WATER_LEVEL_MAX = 9.0;
const float TDS_LOW_THRESHOLD = 400.0;
const float TDS_HIGH_THRESHOLD = 600.0;
const float TEMP_MIN = 20.0;
const float TEMP_MAX = 35.0;
const float HUMIDITY_MIN = 50.0;
const float HUMIDITY_MAX = 80.0;

float tds_calibrationFactor = 0.7; // Calibration factor for TDS sensor
                                                             
float tds_voltage, tdsValue;

void setup() {
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize the DHT sensor
  dht.begin();

  // Set up ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set up TDS relay pin
  pinMode(TdsSensorPin, INPUT);
  pinMode(RelayPin_tds, OUTPUT);
  digitalWrite(RelayPin_tds, HIGH); 
}

void loop() {
  measureWaterLevel();
  delay(1000);
  controlTDS();
  delay(1000);
  measureTemperatureHumidity();
  delay(1000);
  Blynk.run(); 
  delay(1000); 
}

void measureWaterLevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2;

  Serial.print("Water Level: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V1, distance); 

   // Check water level
  if (distance < WATER_LEVEL_MIN) {
    Serial.println("Water level is too HIGH!");
    Blynk.logEvent("high_water_level", "Alert:Water level is too HIGH");
  } else if (distance > WATER_LEVEL_MAX) {
    Serial.println("Water level is too LOW!");
    Blynk.logEvent("low_water_level", "Alert:Water level is too LOW!");
  } else {
    Serial.println("Water level is within the optimal range.");
  }
  
}

void controlTDS() {
  int sensorValue = analogRead(TdsSensorPin);
  tds_voltage = (sensorValue / 4096.0) * 3.3;
  tdsValue = (tds_voltage * 1000) / tds_calibrationFactor;

  Serial.print("TDS Value: ");
  Serial.print(tdsValue);
  Serial.println(" ppm");

  Blynk.virtualWrite(V0, tdsValue); 

  if (tdsValue < TDS_LOW_THRESHOLD) {
    digitalWrite(RelayPin_tds, LOW);
    Serial.println("TDS too low: Adding nutrients.");
  } else if (tdsValue > TDS_HIGH_THRESHOLD) {
    Serial.println("TDS too high");
    Blynk.logEvent("high_tds", "Alert: TDS level is too high!");
  } else {
    digitalWrite(RelayPin_tds, HIGH);
    Serial.println("TDS is optimal.");
  }
  
}

void measureTemperatureHumidity() {
  // Read temperature as Celsius (default)
  float tempC = dht.readTemperature();
  
  // Read humidity
  float humidity = dht.readHumidity();
  
  // Check if any readings failed
  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Blynk.virtualWrite(V2, temperature); 
  Blynk.virtualWrite(V3, humidity); 

  // Check temperature and humidity conditions
  if (temperature < TEMP_MIN || temperature > TEMP_MAX) {
    Serial.println("Temperature is out of range!");
    Blynk.logEvent("temperature", "Alert:Temperature is out of range!");
  } else {
    Serial.println("Temperature is within the optimal range.");
  }

  if (humidity < HUMIDITY_MIN || humidity > HUMIDITY_MAX) {
    Serial.println("Warning: Humidity is out of range!");
    Blynk.logEvent("humidity", "Alert:Humidity is out of range!");
  } else {
    Serial.println("Humidity is within the optimal range.");
  }
  
}
