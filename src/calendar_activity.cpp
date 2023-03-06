#include "calendar_activity.h"

unsigned long long CalendarActivity::remove_hour_min_sec(unsigned long long time) {
  return (time / 86400L) * 86400L;
}

void CalendarActivity::fill_calendarDEBUG() {
  // fill future days offset.
  unsigned long long offset = 6 - get_weekday(today);

  for (int i = 0; i < (COLS * ROWS - offset); ++i) {
    calendar_vith_values[today - (i * 86400L)] = i + 1;
    ;
  }
}

unsigned long long CalendarActivity::get_weekday(unsigned long long day) {
  return (((today / 86400L) + 4) % 7);  //0 is Sunday
}

CalendarActivity::CalendarActivity(String &json, unsigned long long time, unsigned rows, unsigned cols, Adafruit_NeoMatrix *pMatrix) {

  this->pMatrix = pMatrix;
  min_pixel = Pixel(0, 0, 0);
  max_pixel = Pixel(255, 255, 255);

  update(json);
  update(time);
  set_cols(cols);
  set_rows(rows);
  //fill_calendarDEBUG();
}

void CalendarActivity::show() {

  const unsigned long long OFFSET_DAYS = 6 - get_weekday(today);
  const unsigned long long last_comming_day = today + (86400L * OFFSET_DAYS);


  // Min values in calendar range.
  int min_value = 0;
  int max_value = 0;

  for (unsigned row = 0; row < ROWS; ++row) {
    for (unsigned col = 0; col < COLS; ++col) {
      int index = ROWS * (COLS - col) - row - 1;
      int value = calendar_vith_values[last_comming_day - (86400L * index)];
      max_value = (value > max_value) ? value : max_value;
      min_value = (value < min_value) ? value : min_value;
    }
  }

  std::vector<std::vector<Pixel>> v(ROWS, std::vector<Pixel>(COLS));
  /******************/
  	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			Serial.print((int)v[i][j].r);
		}
		Serial.println();
	}
  /*****************/


  pMatrix->fillScreen(0);
  for (unsigned row = 0; row < ROWS; ++row) {
    for (unsigned col = 0; col < COLS; ++col) {
      int index = ROWS * (COLS - col) - row - 1;
      int values = calendar_vith_values[last_comming_day - (86400L * index)];
      if (values) {
        Pixel cur_pixel = MathPixelFlow::map(values, min_value, max_value, min_pixel, max_pixel);

        pMatrix->drawPixel(col, row, pMatrix->Color(cur_pixel.r, cur_pixel.g, cur_pixel.b));
      }
    }
  }
  pMatrix->show();
}

void CalendarActivity::begin() {
  show();
  if (!calendar_vith_values[today]) {
    // set (get_day(today), cols);
  }
}

void CalendarActivity::stop() {
}


void CalendarActivity::set_min_pixel(const Pixel &min_pixel) {
  this->min_pixel = min_pixel;
}

void CalendarActivity::set_max_pixel(const Pixel &max_pixel) {
  this->max_pixel = max_pixel;
}

void CalendarActivity::set_rows(unsigned rows) {
  ROWS = rows;
}

void CalendarActivity::set_cols(unsigned cols) {
  COLS = cols;
}

void CalendarActivity::update(String &json, unsigned long long time) {
  update(json);
  update(time);
}

void CalendarActivity::update(unsigned long long time) {
  today = remove_hour_min_sec(time);
}

void CalendarActivity::update(String &json) {
  calendar_vith_values.clear();


  DynamicJsonDocument doc(20000);
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  const char *name = doc["name"];
  name_this_activity = String(name);

  unsigned long long time;
  int level;

  for (unsigned i = 0;; ++i) {
    time = doc["list"][i]["time"];
    level = doc["list"][i]["level"];
    calendar_vith_values[time] = level;
    //Serial.println(time);
    //Serial.println(level);
    if (!time && !level) {
      break;
    }
  }
}
