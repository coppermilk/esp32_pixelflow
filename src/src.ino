#include "google_sheets_downloader.h"
#include "math_pixelflow.h"
#include "NTPClient.h"
#include "calendar_activity.h"
#include "preloader_activity.h"
#include "pixel.h"
#include "image_db.h"

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


void loop() {
  // put your main code here, to run repeatedly:
  static WiFiUDP ntpUDP;
  static NTPClient timeClient(ntpUDP);
  image_db db;
  timeClient.begin();
  timeClient.update();
  Serial.println(timeClient.getEpochTime());
  Serial.println(timeClient.getDay());
  //matrix.drawPixel(4, 4, matrix.Color(57,211,83));
  GoogleSheetsDownloader gsd("AKfycbxwr4vTb5GeNAJODuxDX57HWeHpwO4hAPuheZaXSAdN9LFb8P1V97U3oz-vnzfcgf3O");
  GoogleSheetsDownloader gsd_sport("AKfycbz4mHPeM4fJu_HjyQgOV_dQncK5MYYiFyC_H-FTu-VbT7yOd56a0y0DadWYJN96Wu9r");
  String json = gsd.get_json();
  String json2 = gsd_sport.get_json();
  Serial.println(json);
  Serial.println(json2);
  CalendarActivity GitHub(json, timeClient.getEpochTime(), 8, 32, &matrix, &db);
  CalendarActivity Sport(json2, timeClient.getEpochTime(), 8, 32, &matrix, &db);
  PreloaderActivity pa(&matrix);
  pa.show();
    GitHub.set_min_pixel(Pixel(14, 68, 41));
    GitHub.set_max_pixel(Pixel(57, 211, 83));
    Sport.set_min_pixel(Pixel(68, 41, 14));
    Sport.set_max_pixel(Pixel(0xf50017));

  while (true) {

    GitHub.show();
    Sport.show();
  }

  //parse(str);
  delay(1000);
}
