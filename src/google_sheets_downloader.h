#pragma once
#include "abstract_downloader_data.h"

class GoogleSheetsDownloader : public AbstractDownloaderData {
private:
  String deployment_id;
public:
  explicit GoogleSheetsDownloader(const String &deployment_id);
  String get_coma_separated_values() override;
};