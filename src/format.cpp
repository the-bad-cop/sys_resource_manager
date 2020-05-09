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
  long sec;
  hour = seconds / 3600;
  minute = seconds % 3600;
  sec = minute % 60;
  minute /= 60;
  return std::to_string(hour) + ":" + std::to_string(minute) + ":" +
         std::to_string(sec);
}