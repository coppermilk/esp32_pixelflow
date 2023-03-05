#pragma once
#include "board_behavior.h"
#include "pixel.h"
#include "Arduino.h"
#include <ArduinoJson.h>
#include <vector>
#include <map>


class CalendarActivity : public BoardBehavior {
private:

  Pixel min_pixel;
  Pixel max_pixel;

  unsigned ROWS;
  unsigned COLS;

  unsigned long long today;

  String name_this_activity;
  std::map<unsigned long long, int> calendar_vith_values;

  unsigned long long remove_hour_min_sec(unsigned long long time);

  void fill_calendarDEBUG();

  unsigned long long get_weekday(unsigned long long day);

public:
  CalendarActivity(String &json, unsigned long long time, unsigned rows, unsigned cols);

  void show();
  void begin() override;
  void stop() override;

  void set_min_pixel(const Pixel& min_pixel);
  void set_max_pixel(const Pixel& max_pixel);

  void set_rows(unsigned rows);
  void set_cols(unsigned cols);

  void update(String &json, unsigned long long time);
  void update(String &json);
  void update(unsigned long long time);
};