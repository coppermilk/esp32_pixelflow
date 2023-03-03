#include "abstract_downloader_data.h"

class GoogleSheetsDownloader: public AbstractDownloaderData{
  public:
  unsigned * downloadData(unsigned array_size) override;
};