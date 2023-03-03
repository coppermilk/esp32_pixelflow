#include "google_sheets_downloader.h"
#include <WiFi.h>
const char* ssid = "UPCED7EFB8";        // type your wifi name
const char* password = "tFax8Er3yycw";  // Type your wifi password

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  GoogleSheetsDownloader gsd("AKfycby3UlTUPrPIuYRvhh-Uo2yePrEQAUrEOp3AdzdNEQlkuhISJ4SUmqh1wcs7zftA3LiM");
  Serial.println(gsd.downloadData());
  delay(100000000);
}
