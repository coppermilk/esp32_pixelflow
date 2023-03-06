#pragma once
#include "board_behavior.h"
#include "pixel.h"
#include "Arduino.h"
#include <Adafruit_NeoMatrix.h>


class PreloaderActivity : public BoardBehavior {
private:
  Adafruit_NeoMatrix *pMatrix;
public:
  PreloaderActivity(Adafruit_NeoMatrix *pMatrix);

  void show();
  void begin() override;
  void stop() override;

};
