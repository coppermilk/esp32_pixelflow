#pragma once
#include "pixel.h"
#include "vector"

class MathPixelFlow{
public:
  static Pixel map(int x, int in_min, int in_max, Pixel &out_min, Pixel &out_max);
  static std::vector<std::vector<Pixel>> get_scroll_frame(const std::vector<std::vector<Pixel>> &frame, int x, int y);
};