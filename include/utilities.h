#ifndef UTILITIES_H
#define UTILITIES_H

#include "types.h"

template <typename Scalar>
bool isInRange(const Scalar &value, const Range<Scalar> &range) {
  if (value < range.first) {
    return false;
  }

  if (value >= range.second) {
    return false;
  }

  return true;
}

#endif  // UTILITIES_H
