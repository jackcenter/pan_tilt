#include "configuration_space.h"

#include <cstddef>
#include <iostream>
#include <string>

static int test_construction(void) {
  ConfigurationSpaceOptions options;
  options.pan_range = {-3.0, 3.0};
  options.pan_resolution = 1;
  options.tilt_range = {-2.0, 0.0};
  options.tilt_resolution = 1;

  ConfigurationSpace configuration_space{options};

  bool did_a_test_fail = false;
  if (options != configuration_space.getOptions()) {
    std::cout << "\tExpected options do not match returned options\n";
    did_a_test_fail = true;
  }

  const size_t expected_pan_configuration_count = 7;
  const size_t pan_configuration_count =
      configuration_space.getPanConfigurationCount();
  if (expected_pan_configuration_count !=
      configuration_space.getPanConfigurationCount()) {
    std::cout
        << "\tExpected pan configuration count does not match return value: "
        << pan_configuration_count << std::endl;
    did_a_test_fail = true;
  }

  const size_t expected_tilt_configuration_count = 3;
  const size_t tilt_configuration_count =
      configuration_space.getTiltConfigurationCount();
  if (expected_tilt_configuration_count != tilt_configuration_count) {
    std::cout
        << "\tExpected tilt configuration count does not match return value: "
        << tilt_configuration_count << std::endl;
    did_a_test_fail = true;
  }

  const Coordinate expected_coordinate{-3, -2};
  if (expected_coordinate != configuration_space.getCoordinateByIndex(0, 0)) {
    std::cout << "\tExpected coordinate does not match returned coordinate\n";
    did_a_test_fail = true;
  }

  return static_cast<int>(did_a_test_fail);
}

int main(void) {
  std::string const test_suite_name{"Test Configuration Space"};
  std::cout << test_suite_name << std::endl;

  std::string const test_name{"test_construction"};
  int const result = test_construction();
  std::cout << "\t" << test_name << "...";
  if (result) {
    std::cout << "\tFAILED\n";
  } else {
    std::cout << "\tPASSED\n";
  }

  return 0;
}