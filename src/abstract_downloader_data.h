#pragma once
#include "Arduino.h"
class AbstractDownloaderData{
  public:
  virtual ~AbstractDownloaderData() = default;
  String downloadData();
};
