#include "configuration_space.h"

#include <cstddef>
#include <stdexcept>
#include <tuple>

#include "types.h"

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

  pan_configuration_count_ =
      static_cast<size_t>((options.pan_range.second - options.pan_range.first) /
                          options.pan_resolution);

  pan_configs_.reserve(pan_configuration_count_);
  for (size_t i = 0; i < pan_configuration_count_; ++i) {
    pan_configs_[i] = {options.pan_range.first + options.pan_resolution * i,
                       options.pan_range.first +
                           options.pan_resolution * (i + 1)};
  }

  tilt_configuration_count_ = static_cast<size_t>(
      (options.tilt_range.second - options.tilt_range.first) /
      options.tilt_resolution);

  tilt_configs_.reserve(tilt_configuration_count_);
  for (size_t i = 0; i < tilt_configuration_count_; ++i) {
    pan_configs_[i] = {options.tilt_range.first + options.tilt_resolution * i,
                       options.tilt_range.first +
                           options.tilt_resolution * (i + 1)};
  }
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