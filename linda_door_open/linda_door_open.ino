#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

char tuple[] = "tuple={\"where\":\"delta\",\"type\":\"door\",\"cmd\":\"open\",\"who\":\"M5Stack\"}";
String ts = String(tuple);

const char* ssid = "";
const char* password = "";
const char* lindaUrl = "";

void clearScrean() {
  M5.Lcd.clear(DARKCYAN);
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("Linda Door Open");
  M5.Lcd.setCursor(3, 35);
}

void displayMessage(String message){
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println(message);
}

void setup() {
  // put your setup code here, to run once:
  M5.begin(true, false, true);
  clearScrean();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    displayMessage("connecting...");
    delay(1000);
  }
  clearScrean();
  displayMessage("connected!");
}

void doorOpen() {
  displayMessage("Door Opening...");
  HTTPClient http;
  http.begin(lindaUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(ts);
  http.end();
  if (httpCode == 200) {
    displayMessage("Door Opened!");
  } else {
    displayMessage("Something went wrong:(");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.update();
  if (M5.BtnB.wasReleased()) {
    doorOpen();
  } else if (M5.BtnA.wasReleased()) {
    clearScrean();
  }
}
