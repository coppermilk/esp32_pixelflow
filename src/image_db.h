#pragma once
#include <vector>
#include <map>
#include "Arduino.h"
class image_db {
private:
	 void generate();
	 std::map <String, std::vector<std::vector<unsigned>>> database;
public:
	image_db();
  
	std::vector<std::vector<unsigned>> get_image_by_name(const String& str);
  /*
	image_db(const image_db&) = delete;
	image_db(const image_db&&) = delete;

	image_db& operator=(const image_db&) = delete;

	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;

	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;*/
};