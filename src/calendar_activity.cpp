#include <utility>
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

CalendarActivity::CalendarActivity(String &json, unsigned long long time, unsigned rows, unsigned cols, Adafruit_NeoMatrix *pMatrix, image_db * pImageDB) {

  this->pMatrix = pMatrix;
  min_pixel = Pixel(0, 0, 0);
  max_pixel = Pixel(255, 255, 255);

  update(json);
  update(time);
  //set_cols(cols);
  //set_rows(rows);
  ROWS = rows;
  COLS = cols;
  DAYS_IN_WEEK = 7;
  this->pImageDB = pImageDB;
  //fill_calendarDEBUG();
}

std::pair<int, int> CalendarActivity::get_min_max_value() {

  const unsigned long long OFFSET_DAYS = 6 - get_weekday(today);
  const unsigned long long last_comming_day = today + (86400L * OFFSET_DAYS);

  //const unsigned DAYS_IN_WEEK = 7;

  // Min values in calendar range.
  int min_value = 0;
  int max_value = 0;

  for (unsigned row = 0; row < DAYS_IN_WEEK; ++row) {
    for (unsigned col = 0; col < COLS; ++col) {
      int index = DAYS_IN_WEEK * (COLS - col) - row - 1;
      int value = calendar_vith_values[last_comming_day - (86400L * index)];
      max_value = (value > max_value) ? value : max_value;
      min_value = (value < min_value) ? value : min_value;
    }
  }
  return std::make_pair(min_value, max_value);
}

void CalendarActivity::show() {
  std::vector<std::vector<Pixel>>frame = get_frame();
  for (int i = COLS; i >= 0; --i) {
    std::vector<std::vector<Pixel>> scrolled_frame = MathPixelFlow::get_scroll_frame(frame, i, 0);
    pMatrix->fillScreen(0);
    for (unsigned row = 0; row < 8; ++row) {
      for (unsigned col = 0; col < COLS; ++col) {
        Pixel p = scrolled_frame[row][col];
        pMatrix->drawPixel(col, row, pMatrix->Color(p.r, p.g, p.b));
      }
    }
    pMatrix->show();
     if(i){
        delay(60/((i > 0) ? i : -i));
    }
   
  }

  delay(20000);
  for (int i = 0; i >= -33; --i) {
    std::vector<std::vector<Pixel>> scrolled_frame = MathPixelFlow::get_scroll_frame(frame, i,0);
    pMatrix->fillScreen(0);
    for (unsigned row = 0; row < ROWS; ++row) {
      for (unsigned col = 0; col < COLS; ++col) {
        Pixel p = scrolled_frame[row][col];
        pMatrix->drawPixel(col, row, pMatrix->Color(p.r, p.g, p.b));
      }
    }
    pMatrix->show();
     if(i){
        delay(60/((i > 0) ? i : -i));
    }
  }

}

void CalendarActivity::begin() {
  show();
  if (!calendar_vith_values[today]) {
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
    if (!time && !level) {
      break;
    }
  }
}

std::vector<std::vector<Pixel>> CalendarActivity::get_frame(){


  // Fill callendar.
  const unsigned long long OFFSET_DAYS = 6 - get_weekday(today);
  const unsigned long long last_comming_day = today + (86400L * OFFSET_DAYS);

  std::vector<std::vector<Pixel>> cur_frame(ROWS, std::vector<Pixel>(COLS));
  std::pair<int, int> min_max = get_min_max_value();
  for (unsigned row = 0; row < DAYS_IN_WEEK; ++row) {
    for (unsigned col = 0; col < COLS; ++col) {
      int index = DAYS_IN_WEEK * (COLS - col) - row - 1;
      int values = calendar_vith_values[last_comming_day - (86400L * index)];
      if (values) {
        Pixel cur_pixel = MathPixelFlow::map(values, min_max.first, min_max.second, min_pixel, max_pixel);
        cur_frame[row][col] = cur_pixel;
      }
    }
  }

  // Override frame.
  std::vector<std::vector<unsigned>> image = pImageDB->get_image_by_name(name_this_activity);
  if(!image.empty()){
      for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
          cur_frame[i][j] = Pixel(image[i][j]);
          Serial.println(image[i][j]);
        }
    }
  }


  return cur_frame;
}

