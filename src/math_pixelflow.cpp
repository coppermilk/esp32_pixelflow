#pragma once
#include "math_pixelflow.h"
#include "pixel.h"
template<typename T>
T max(T* pArr, unsigned long long size) {
  if (!pArr || !size) {
    return T{};
  } else {
    T max_num = *pArr;
    for (unsigned long long i = 0; i < size; ++i) {
      if (pArr[i] > max_num) {
        max_num = pArr[i];
      }
    }
    return max_num;
  }
}

template<typename T>
T min(T* pArr, unsigned long long size) {
  if (!pArr || !size) {
    return T{};
  } else {
    T min_num = *pArr;
    for (unsigned long long i = 0; i < size; ++i) {
      if (pArr[i] < min_num) {
        min_num = pArr[i];
      }
    }
    return min_num;
  }
}

Pixel map(int x, int in_min, int in_max, Pixel out_min, Pixel out_max) {

  // If x is zero, return a black pixel
  if (!x) {
    return { 0, 0, 0 };
  } else {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    if (x == 1) {
      // Clamp the ratio between 0 and 1
      r = out_min.r;
      g = out_min.g;
      b = out_min.b;
    } else {
      // Interpolate between the output colors
      r = (x - in_min) * (out_max.r - out_min.r) / (in_max - in_min) + out_min.r;
      g = (x - in_min) * (out_max.g - out_min.g) / (in_max - in_min) + out_min.g;
      b = (x - in_min) * (out_max.b - out_min.b) / (in_max - in_min) + out_min.b;
    }
    return { r, g, b };
  }
}
