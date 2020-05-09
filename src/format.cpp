#include "format.h"

#include <string>

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long hour;
  long minute;
  hour = seconds / 3600;
  seconds %= 3600;
  minute = seconds / 60;
  seconds %= 60;
  string temp, hhmmss = {};
  temp = std::to_string(hour);
  temp.insert(0, 2 - temp.length(), '0');
  hhmmss += temp + ":";
  temp = std::to_string(minute);
  temp.insert(0, 2 - temp.length(), '0');
  hhmmss += temp + ":";
  temp = std::to_string(seconds);
  temp.insert(0, 2 - temp.length(), '0');
  hhmmss += temp;
  return hhmmss;
}