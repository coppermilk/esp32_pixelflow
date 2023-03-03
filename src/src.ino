#include "google_sheets_downloader.h"
#include "math_pixelflow.h"

#include <WiFi.h>
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
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  GoogleSheetsDownloader gsd("AKfycby3UlTUPrPIuYRvhh-Uo2yePrEQAUrEOp3AdzdNEQlkuhISJ4SUmqh1wcs7zftA3LiM");
  Serial.println(gsd.get_coma_separated_values());
  delay(100000000);
}
