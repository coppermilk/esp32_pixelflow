#include "frame.h"

Frame::Frame(unsigned ROWS, unsigned COLS)
{
	this->COLS = COLS;
	this->ROWS = ROWS;
	std::vector<std::vector<Pixel>> tmp(ROWS, std::vector<Pixel>(COLS));
	frame = tmp;
}

std::vector<std::vector<Pixel>> Frame::get_scroll_frame(int x = 0, int y = 0)
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

void Frame::draw_pixel(unsigned x, unsigned y, const Pixel& pixel)
{
		frame[x][y] = pixel;
}

void Frame::print() {
	for (int i = 0; i < frame.size(); ++i) {
		for (int j = 0; j < frame[i].size(); ++j) {
			Serial.print(String(frame[i][j].g)  + " ");
		}
    Serial.println();
	}
}