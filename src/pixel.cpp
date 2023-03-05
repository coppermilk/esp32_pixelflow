#pragma once
#include "pixel.h"

Pixel::Pixel(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Pixel::Pixel()
{
	r = g = b = 0;
}
