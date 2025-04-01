#include "utilities.h"

#include <iostream>
#include <string>

#include "types.h"

static bool test_isInRangeDouble(void) {
  bool did_a_test_fail = false;

  {
    const Range<double> range{-1.0, 2.0};
    const double value{-2.0};
    const bool expected_result = false;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  {
    const Range<double> range{-1.0, 2.0};
    const double value{-1.0};
    const bool expected_result = true;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  {
    const Range<double> range{-1.0, 2.0};
    const double value{0.0};
    const bool expected_result = true;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  {
    const Range<double> range{-1.0, 2.0};
    const double value{1.0};
    const bool expected_result = true;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  {
    const Range<double> range{-1.0, 2.0};
    const double value{2.0};
    const bool expected_result = false;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  {
    const Range<double> range{-1.0, 2.0};
    const double value{3.0};
    const bool expected_result = false;
    const bool result = isInRange(value, range);
    if (expected_result != result) {
      std::cout << "isInRange returned " << result << " for value (" << value
                << "} in range [" << range.first << ", " << range.second
                << ")\n";
      did_a_test_fail = true;
    }
  }

  return did_a_test_fail;
}

int main(void) {
  const std::string test_suite_name{"Test Utilities"};
  std::cout << test_suite_name << std::endl;

  bool did_a_test_fail = false;

  {
    const std::string test_name{"test_isInRange"};
    const bool is_test_a_failure = test_isInRangeDouble();

    std::cout << "\t" << test_name << "...";
    if (is_test_a_failure) {
      std::cout << "\tFAILED" << std::endl;
      did_a_test_fail = true;
    } else {
      std::cout << "\tPASSED" << std::endl;
    }
  }

  if (did_a_test_fail) {
    std::cout << "\n\t" << test_suite_name << ": FAILED\n";
  } else {
    std::cout << "\n\t" << test_suite_name << ": PASSED\n";
  }

  return 0;
}