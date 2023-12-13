#include <Wire.h>
#include <HX711.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

#define DOUT_PIN D1
#define CLK_PIN D2
#define BUZZER_PIN D5

HX711 scale;
MPU6050 mpu;

const char *ssid = "Galaxy A3102DE";
const char *password = "csli6803";
const char *thingSpeakApiKey = "8B6EEAVMP38BMJ2S";
const unsigned long channelNumber = 2370857; 

//float weightCalibrationFactor = 1.0 * 2;

void initializeSensors() {
  Serial.println("Initializing sensors...");
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale();
  scale.set_scale(81750);

  Wire.begin(D3, D4);
  mpu.initialize();
  delay(100);
  mpu.CalibrateGyro(1.0 / 1000);
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  Serial.println("Sensors initialized");
}
WiFiClient client; 
void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup...");

  initializeSensors();

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(250);
  Serial.print(".");
}
Serial.println("Connected to WiFi");

  ThingSpeak.begin(client);

  Serial.println("Setup completed.");
}

void loop() {
  float weight = scale.get_units(10);

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  unsigned long currentMillis = millis();

  Serial.print("Timestamp: ");
  Serial.print(currentMillis / 1000);
  Serial.print("\tWeight: ");
  Serial.print(weight);
  Serial.print(" g\t");

  Serial.print("Acceleration: ");
  Serial.print(abs(ax)-3562+1550);
  Serial.print(" ");
  Serial.print(abs(ay)-15639-250);
  Serial.print(" ");
  Serial.println(abs(az)-2338+650);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, weight);
  ThingSpeak.setField(2, abs(ax)-3562+1550);
  ThingSpeak.setField(3, abs(ay)-15639-250);
  ThingSpeak.setField(4, abs(az)-2338+650);

  if (weight <= -2.80) {
    tone(BUZZER_PIN, 1000, 500);
    delay(1000);
  }

  ThingSpeak.writeFields(channelNumber, thingSpeakApiKey);
  int writeResult = ThingSpeak.writeFields(channelNumber, thingSpeakApiKey);
  Serial.print("Write result: ");
  Serial.println(writeResult);


  delay(100); 
}
