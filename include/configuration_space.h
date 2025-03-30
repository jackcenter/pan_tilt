#ifndef CONFIGURATION_SPACE_H
#define CONFIGURATION_SPACE_H

#include <cstddef>
#include <utility>
#include <vector>

#include "types.h"

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
