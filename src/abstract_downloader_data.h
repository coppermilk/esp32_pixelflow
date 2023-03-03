#pragma once
#include "Arduino.h"
class AbstractDownloaderData{
  public:
  virtual ~AbstractDownloaderData() = default;
  virtual String get_coma_separated_values();
};
