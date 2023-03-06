#pragma once
#include "pixel.h"
#include <vector>


class Frame
{
	 unsigned COLS;
	 unsigned ROWS;
public:
	Frame(unsigned ROWS, unsigned COLS);
	std::vector<std::vector<Pixel>> frame;
	std::vector<std::vector<Pixel>> get_scroll_frame(int x, int y);
	void draw_pixel(unsigned x, unsigned y, const Pixel& pixel);
	void print();
};

