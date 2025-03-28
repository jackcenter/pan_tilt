#ifndef CONFIGURATION_SPACE_H
#define CONFIGURATION_SPACE_H

#include <cstddef>
#include <utility>
#include <vector>

using Coordinate = std::pair<double, double>;
using Range = std::pair<double, double>;

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

  Coordinate getCoordinateByIndex(const size_t pan_config,
                                  const size_t tilt_config) const;
  ConfigurationSpaceOptions getOptions(void) const;
  size_t getPanConfigurationCount(void) const;
  size_t getTiltConfigurationCount(void) const;

private:
  ConfigurationSpaceOptions options_;
  size_t pan_configuration_count_;
  size_t tilt_configuration_count_;
  std::vector<std::vector<Coordinate>> coordinate_grid_;
};

#endif // CONFIGURATION_SPACE_H
