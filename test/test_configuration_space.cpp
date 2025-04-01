#include "configuration_space.h"

#include <cstddef>
#include <iostream>
#include <optional>
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

static bool test_getConfigurationRange(void) {
  bool did_a_test_fail = false;

  ConfigurationSpaceOptions options;
  options.pan_range = {-3.0, 3.0};
  options.pan_resolution = 1;
  options.tilt_range = {-2.0, 0.0};
  options.tilt_resolution = 1;

  ConfigurationSpace configuration_space{options};

  {
    const ConfigurationState state{.pan = -2.5, .tilt = -1.5};
    const std::optional<ConfigurationRange> config_range{
        configuration_space.getConfigurationRange(state)};

    if (!config_range.has_value()) {
      std::cout << "`config_range` does not contain a value.\n";
      did_a_test_fail = true;
    } else {
      const ConfigurationRange expected_config_range{.pan = {-3.0, -2.0},
                                                     .tilt = {-2.0, -1.0}};

      if (expected_config_range != config_range.value()) {
        std::cout << "`config_range` does not match `expected_config_range`\n";
      }
    }
  }

  return did_a_test_fail;
}

int main(void) {
  const std::string test_suite_name{"Test Configuration Space"};
  std::cout << test_suite_name << std::endl;

  bool did_a_test_fail = false;

  {
    const std::string test_name{"test_construction"};
    const bool is_test_a_failure = test_construction();
    std::cout << "\t" << test_name << "...";
    if (is_test_a_failure) {
      std::cout << "\t\tFAILED\n";
      did_a_test_fail = true;
    } else {
      std::cout << "\t\tPASSED\n";
    }
  }

  {
    const std::string test_name{"test_getConfigurationRange"};
    const bool is_test_a_failure = test_getConfigurationRange();
    std::cout << "\t" << test_name << "...";
    if (is_test_a_failure) {
      std::cout << "\tFAILED\n";
      did_a_test_fail = true;
    } else {
      std::cout << "\tPASSED\n";
    }
  }

  if (did_a_test_fail) {
    std::cout << "\n\t" << test_suite_name << ": FAILED\n";
  } else {
    std::cout << "\n\t" << test_suite_name << ": PASSED\n";
  }

  return 0;
}