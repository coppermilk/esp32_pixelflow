#pragma once
#include "abstract_downloader_data.h"

class GoogleSheetsDownloader: public AbstractDownloaderData{
  private:
  String GOOGLE_SCRIPT_ID;
  public:
  explicit GoogleSheetsDownloader(String);
  String get_coma_separated_values() override;
};