#pragma once
#include "board_behavior.h"
#include "pixel.h"
#include "Arduino.h"
#include "math_pixelflow.h"
#include <ArduinoJson.h>
#include <Adafruit_NeoMatrix.h>
#include <vector>
#include <map>


class CalendarActivity : public BoardBehavior {
private:

  Pixel min_pixel;
  Pixel max_pixel;

  unsigned ROWS;
  unsigned COLS;
  unsigned DAYS_IN_WEEK;

  unsigned long long today;
  Adafruit_NeoMatrix *pMatrix;
  String name_this_activity;
  std::map<unsigned long long, int> calendar_vith_values;
  unsigned long long remove_hour_min_sec(unsigned long long time);
  void fill_calendarDEBUG();

  unsigned long long              get_weekday(unsigned long long day);
  std::pair<int, int>             get_min_max_value();
  std::vector<std::vector<Pixel>> get_frame();

public:
  CalendarActivity(String &json, unsigned long long time, unsigned rows, unsigned cols, Adafruit_NeoMatrix *pMatrix);

  void show();
  void begin() override;
  void stop() override;

  void set_min_pixel(const Pixel& min_pixel);
  void set_max_pixel(const Pixel& max_pixel);

  void update(String &json, unsigned long long time);
  void update(String &json);
  void update(unsigned long long time);
};


