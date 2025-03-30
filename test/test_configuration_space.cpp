#include "configuration_space.h"

#include <cstddef>
#include <iostream>
#include <string>

#include "types.h"

static bool test_construction(void) {
  bool did_a_test_fail = false;
  
  ConfigurationSpaceOptions options;
  options.pan_range = {-3.0, 3.0};
  options.pan_resolution = 1;
  options.tilt_range = {-2.0, 0.0};
  options.tilt_resolution = 1;

  ConfigurationSpace configuration_space{options};

  if (options != configuration_space.getOptions()) {
    std::cout << "\tExpected options do not match returned options\n";
    did_a_test_fail = true;
  }

  const size_t expected_pan_configuration_count = 6;
  const size_t pan_configuration_count =
      configuration_space.getPanConfigurationCount();
  if (expected_pan_configuration_count !=
      configuration_space.getPanConfigurationCount()) {
    std::cout
        << "\tExpected pan configuration count does not match return value: "
        << pan_configuration_count << std::endl;
    did_a_test_fail = true;
  }

  const size_t expected_tilt_configuration_count = 2;
  const size_t tilt_configuration_count =
      configuration_space.getTiltConfigurationCount();
  if (expected_tilt_configuration_count != tilt_configuration_count) {
    std::cout
        << "\tExpected tilt configuration count does not match return value: "
        << tilt_configuration_count << std::endl;
    did_a_test_fail = true;
  }

  return did_a_test_fail;
}

int main(void) {
  const std::string test_suite_name{"Test Configuration Space"};
  std::cout << test_suite_name << std::endl;

  const std::string test_name{"test_construction"};
  const bool is_test_a_failure = test_construction();
  std::cout << "\t" << test_name << "...";
  if (is_test_a_failure) {
    std::cout << "\tFAILED\n";
  } else {
    std::cout << "\tPASSED\n";
  }

  return 0;
}