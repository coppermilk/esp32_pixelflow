#pragma once

#include <HTTPClient.h>
#include "google_sheets_downloader.h"
GoogleSheetsDownloader::GoogleSheetsDownloader(const String &deployment_id){
  this->deployment_id = deployment_id;
}

String GoogleSheetsDownloader::get_coma_separated_values() {
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + deployment_id + "/exec?read";
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
  http.end();
  return payload;
}
