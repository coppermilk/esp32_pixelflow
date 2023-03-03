#pragma once

#include <HTTPClient.h>
#include "google_sheets_downloader.h"
GoogleSheetsDownloader::GoogleSheetsDownloader(String GOOGLE_SCRIPT_ID){
  this->GOOGLE_SCRIPT_ID = GOOGLE_SCRIPT_ID;
}

String get_coma_separated_values::downloadData() {
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?read";
  Serial.println("Reading Data From Google Sheet.....");
  http.begin(url.c_str());
  //Removes the error "302 Moved Temporarily Error"
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  //Get the returning HTTP status code
  int httpCode = http.GET();
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);

  String payload;
  if (httpCode <= 0) {
    Serial.println("Error on HTTP request");
    http.end();
  } else if (httpCode == 200) {
    payload = http.getString();
  }
  //-------------------------------------------------------------------------------------
  http.end();
  return payload;
}
