#include <iostream>
#include <string>

static int test_say_hello(void) { return 0; }

int main(void) {
  std::string const test_suite_name{"Test Utilities"};
  std::cout << test_suite_name << std::endl;

  std::string const test_name {"test_say_hello"};
  int const result = test_say_hello();
  std::cout << "\t" << test_name << "..." ;
  if (result) {
    std::cout << "\tFAILED" << std::endl;
  } else {
    std::cout << "\tPASSED" << std::endl;
  }

  return 0;
}