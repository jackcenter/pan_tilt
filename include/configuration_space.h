#ifndef CONFIGURATION_SPACE_H
#define CONFIGURATION_SPACE_H

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "types.h"

struct ConfigurationState {
  double pan;
  double tilt;
};

struct ConfigurationRange {
  Range pan;
  Range tilt;
};

bool operator==(const ConfigurationRange &lhs, const ConfigurationRange &rhs);
bool operator!=(const ConfigurationRange &lhs, const ConfigurationRange &rhs);

struct ConfigurationSpaceOptions {
  Range pan_range;
  double pan_resolution;
  Range tilt_range;
  double tilt_resolution;
};

bool operator==(const ConfigurationSpaceOptions &lhs,
                const ConfigurationSpaceOptions &rhs);
bool operator!=(const ConfigurationSpaceOptions &lhs,
                const ConfigurationSpaceOptions &rhs);

class ConfigurationSpace {
public:
  ConfigurationSpace(const ConfigurationSpaceOptions &options);

  const std::optional<ConfigurationRange>
  getConfigurationRange(const ConfigurationState &state) const;

  ConfigurationSpaceOptions getOptions(void) const;

  size_t getPanConfigurationCount(void) const;

  size_t getTiltConfigurationCount(void) const;

private:
  ConfigurationSpaceOptions options_;

  size_t pan_configuration_count_;
  std::vector<Range> pan_configs_;

  size_t tilt_configuration_count_;
  std::vector<Range> tilt_configs_;
};

#endif // CONFIGURATION_SPACE_H
