#ifndef TYPES_H
#define TYPES_H

#include <utility>

template <typename Scalar>
using Coordinate = std::pair<Scalar, Scalar>;

template <typename Scalar>
using Range = std::pair<Scalar, Scalar>;

template <typename Scalar>
using CoordinateRange = std::pair<Coordinate<Scalar>, Coordinate<Scalar>>;

#endif  // TYPES_H
