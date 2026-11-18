#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";
const char* topic = "YOUR_KIWISIOT_TOPIC_ID";

#define EC_PIN A0

KiwisIoT kiwisiot(ssid, pass, topic);

unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("Water EC Monitoring");

  kiwisiot.begin();
}

void loop() {
  kiwisiot.run();

  if (millis() - lastSend >= 2000) {
    lastSend = millis();

    int ecRawValue = analogRead(EC_PIN);

    Serial.print("EC Raw Value: ");
    Serial.println(ecRawValue);

    // Send raw reading to KiwisIoT Channel 0
    kiwisiot.send("0", String(ecRawValue));
  }

  delay(10);
}