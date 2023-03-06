#pragma once
#include "math_pixelflow.h"

Pixel MathPixelFlow::map(int x, int in_min, int in_max, Pixel &out_min, Pixel &out_max) {

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


std::vector<std::vector<Pixel>> MathPixelFlow::get_scroll_frame(const std::vector<std::vector<Pixel>> &frame, int x, int y)
{
	// Corner case.
	if (frame.empty()) {
		return {};
	}

	const size_t rows = frame.size();
	const size_t cols = frame[0].size();

	std::vector<std::vector<Pixel>> frame_scrolled(rows, std::vector<Pixel>(cols));

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < cols; ++j) {
			// Check if the shifted pixel is within the bounds of the input vector.
			if ((i - y) >= 0 && (i - y) < rows
				&& (j - x) >= 0 && (j - x) < cols) {

				frame_scrolled[i][j] = frame[i - y][j - x];
			}
		}
	}

	return frame_scrolled;
}