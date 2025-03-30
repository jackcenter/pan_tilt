#include "utilities.h"

#include <iostream>

bool isInRange(const double &value, const Range &range) {
  if (value < range.first) {
    return false;
  }

  if (value >= range.second) {
    return false;
  }

  return true;
}
