#pragma once
#include "Arduino.h"
class Pixel {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	Pixel(uint8_t, uint8_t, uint8_t);
	Pixel();
};
