#pragma once
#include "pixel.h"

class MathPixelFlow{
public:
  static Pixel map(int x, int in_min, int in_max, Pixel &out_min, Pixel &out_max);
};