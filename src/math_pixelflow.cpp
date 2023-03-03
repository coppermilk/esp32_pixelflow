#pragma once
#include "math_pixelflow.h"

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