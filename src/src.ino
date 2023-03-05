#include "google_sheets_downloader.h"
#include "math_pixelflow.h"
#include "NTPClient.h"
#include "calendar_activity.h"

//#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "UPCED7EFB8";        // type your wifi name
const char* password = "tFax8Er3yycw";  // Type your wifi password

#define PIN_MATRIX 25
#define MATRIX_W 32
#define MATRIX_H 8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, PIN_MATRIX,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  matrix.begin();
  matrix.setBrightness(20);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.begin(115200);
}
/*
void parse(const String& json) {
  DynamicJsonDocument doc(20000);
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  const char* name = doc["name"];
  Serial.println(name);
  unsigned long long time;
  int level;

  for (unsigned i = 0;; ++i) {
    time = doc["list"][i]["time"];
    level = doc["list"][i]["level"];
    Serial.println(time);
    Serial.println(level);
    if (!time && !level) {
      break;
    }
  }
}
*/
/*
int x    = matrix.width();
int pass = 0;
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
void loop() {
  matrix.fillScreen(0);
  auto pMatrix = &matrix;
  matrix.setCursor(x, 0);
  matrix.print(F("Howdy"));
  if(--x < -36) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);
}

*/

void loop() {
  // put your main code here, to run repeatedly:
  static WiFiUDP ntpUDP;
  static NTPClient timeClient(ntpUDP);
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getEpochTime());
  Serial.println(timeClient.getDay());
 matrix.drawPixel(4, 4, matrix.Color(200, 200, 200));
  GoogleSheetsDownloader gsd("AKfycbxwr4vTb5GeNAJODuxDX57HWeHpwO4hAPuheZaXSAdN9LFb8P1V97U3oz-vnzfcgf3O");
  String json = gsd.get_json();
  Serial.println(json);

  CalendarActivity ca(json, timeClient.getEpochTime(), 7, 32, &matrix);
  ca.show();

  //parse(str);
  delay(100000);
}
