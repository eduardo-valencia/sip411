// Assignment from class CSC230

#include "secrets.h"
#include <M5StickC.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

#define LED_BUILTIN 10

String fireStatus = "";

void setup() {
  M5.begin();

  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to " ) ;
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("LED_STATUS", "OFF");

  M5.Lcd.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 15);
  M5.Lcd.println("Connected ");
  M5.Lcd.print(WIFI_SSID);
}


void loop() {
  // Get the LED's status from the database
  fireStatus = Firebase.getString("LED_STATUS");

  // If the LED should be off
  if (fireStatus == "OFF")
  {
    // Print that it will be turned off
    Serial.println("Led Turned OFF");
    // Turn it off
    digitalWrite(LED_BUILTIN, HIGH);
    // If the LED should be on
  } else if (fireStatus == "ON") {
    // Print that it will be turned on
    Serial.println("Led Turned ON");
    // Turn it on
    digitalWrite(LED_BUILTIN, LOW);
  // Otherwise
  } else {
    // Print that the value is incorrect
    Serial.println("Wrong Credential! Please send ON/OFF");
  }

  // Wait 5 seconds
  delay(5000);
}
