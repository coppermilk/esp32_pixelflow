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
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.begin(115200);
}

int x = matrix.width();
int pass = 0;
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};


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
  GoogleSheetsDownloader gsd_sport_nata("AKfycby1XiG4EVRF5Vx-m6iw84u3CVMVDB44yhvdyNDfhn65aLmOHR1M2jUzufZW0HT_nWnE");
  GoogleSheetsDownloader gsd_duo("AKfycbzy04GbrBssUtUCCokoqWFWQkXiEhKQA1zryEAdxgjuCoUTX_BbTMzy2_mTy8ppt2y4");
  String json = gsd.get_json();
  String json2 = gsd_sport.get_json();
  String json3 = gsd_duo.get_json();
  String json4 = gsd_sport_nata.get_json();

  Serial.println(json);
  Serial.println(json2);
  Serial.println(json3);
  Serial.println(json4);

  CalendarActivity GitHub(json, timeClient.getEpochTime(), 8, 32, &matrix, &db);
  delay(1000);
  CalendarActivity Sport(json2, timeClient.getEpochTime(), 8, 32, &matrix, &db);
  delay(1000);
  CalendarActivity Duo(json3, timeClient.getEpochTime(), 8, 32, &matrix, &db);
  delay(1000);
  CalendarActivity SportNata(json4, timeClient.getEpochTime(), 8, 32, &matrix, &db);

  PreloaderActivity pa(&matrix);
  pa.show();
  GitHub.set_min_pixel(Pixel(14, 68, 41));
  GitHub.set_max_pixel(Pixel(57, 211, 83));
  Sport.set_min_pixel(Pixel(68, 41, 14));
  Sport.set_max_pixel(Pixel(0xf50017));
  Duo.set_min_pixel(Pixel(0xEB932F));
  Duo.set_max_pixel(Pixel(0xFAC03D));
  SportNata.set_min_pixel(Pixel(0x655A00));
  SportNata.set_max_pixel(Pixel(0xBBFF00));


  while (true) {
    pa.show();
    GitHub.show();
    SportNata.show();
     Sport.show();
     Duo.show();
    matrix.show();
    for (int i = 0; i < 20000;i +=100) {
      matrix.fillScreen(0);
      matrix.setCursor(x, 0);
      matrix.print(F("30 Days for research IT"));
      if (--x < -150) {
        x = matrix.width();
        matrix.setTextColor(colors[0]);
      }
      Serial.println(x);
      matrix.show();
      delay(100);
    }
  }

  //parse(str);
  delay(1000);
}
