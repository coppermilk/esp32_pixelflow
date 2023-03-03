#pragma once
#include "abstract_downloader_data.h"
#include "Arduino.h"

class GoogleSheetsDownloader: public AbstractDownloaderData{
  public:
  String downloadData() override;
};