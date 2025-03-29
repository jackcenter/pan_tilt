#include "configuration_space.h"

#include <cstddef>
#include <stdexcept>
#include <tuple>

bool operator==(const ConfigurationSpaceOptions &lhs,
                const ConfigurationSpaceOptions &rhs) {
  return (std::make_tuple(lhs.pan_range, lhs.pan_resolution, lhs.tilt_range,
                          lhs.tilt_resolution) ==
          std::make_tuple(rhs.pan_range, rhs.pan_resolution, rhs.tilt_range,
                          rhs.tilt_resolution));
}

bool operator!=(const ConfigurationSpaceOptions &lhs,
                const ConfigurationSpaceOptions &rhs) {
  return !(lhs == rhs);
}

ConfigurationSpace::ConfigurationSpace(const ConfigurationSpaceOptions &options)
    : options_{options} {
  if (options.pan_range.first > options.pan_range.second) {
    throw std::invalid_argument(
        "`pan_range.first` cannot be larger than `pan_range.second");
  }

  if (options_.pan_resolution <= 0) {
    throw std::invalid_argument(
        "`pan_resolution` must be non-zero and positive");
  }

  if (options.tilt_range.first > options.tilt_range.second) {
    throw std::invalid_argument(
        "`tilt_range.first` cannot be larger than `tilt_range.second");
  }

  if (options.tilt_resolution <= 0) {
    throw std::invalid_argument(
        "`tilt_resolution` must be non-zero and positive");
  }

  // Calculate the coordinate grid size
  pan_configuration_count_ =
      static_cast<size_t>((options.pan_range.second - options.pan_range.first) /
                          options.pan_resolution);

  tilt_configuration_count_ = static_cast<size_t>(
      (options.tilt_range.second - options.tilt_range.first) /
      options.tilt_resolution);

  // Reserve space for the coordinate grid
  coordinate_grid_.reserve(pan_configuration_count_);
  for (size_t i = 0; i < pan_configuration_count_; ++i) {
    coordinate_grid_[i].reserve(tilt_configuration_count_);
  }

  // Create the grid of coordinates based on the options
  for (size_t pan_config_idx = 0; pan_config_idx < pan_configuration_count_;
       ++pan_config_idx) {
    for (size_t tilt_config_idx = 0;
         tilt_config_idx < tilt_configuration_count_; ++tilt_config_idx) {
      const Coordinate minumum{
          options.pan_range.first + options.pan_resolution * pan_config_idx,
          options.tilt_range.first + options.tilt_resolution * tilt_config_idx};

      const Coordinate maximum{
          options.pan_range.first +
              options.pan_resolution * (pan_config_idx + 1),
          options.tilt_range.first +
              options.tilt_resolution * (tilt_config_idx + 1)};

      coordinate_grid_[pan_config_idx][tilt_config_idx] =
          CoordinateRange{minumum, maximum};
    }
  }
}

CoordinateRange
ConfigurationSpace::getCoordinateRangeByIndex(const size_t pan_config,
                                              const size_t tilt_config) const {
  if (pan_config >= pan_configuration_count_) {
    throw std::invalid_argument(
        "`pan_config` exceeds `pan_configuration_count_`");
  }

  if (tilt_config >= tilt_configuration_count_) {
    throw std::invalid_argument(
        "`tilt_config` exceeds `tilt_configuration_count_`");
  }
  return coordinate_grid_[pan_config][tilt_config];
}

ConfigurationSpaceOptions ConfigurationSpace::getOptions(void) const {
  return options_;
}

size_t ConfigurationSpace::getPanConfigurationCount(void) const {
  return pan_configuration_count_;
}
size_t ConfigurationSpace::getTiltConfigurationCount(void) const {
  return tilt_configuration_count_;
}