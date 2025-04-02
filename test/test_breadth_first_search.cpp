#include "breadth_first_search.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

static bool test_construction(void) {
  bool did_a_test_fail = false;

  const std::vector<Node> nodes{};
  const std::vector<Edge> edges{};
  const Graph graph{.nodes = nodes, .edges = edges};

  BreadthFirstSearch bfs{graph};

  return did_a_test_fail;
}

static bool test_getPath(void) {
  bool did_a_test_fail = false;

  const std::vector<Node> nodes{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 1}};
  const std::vector<Edge> edges{
      {{0, 0}, {0, 1}}, {{0, 1}, {0, 2}}, {{0, 1}, {1, 1}}, {{0, 2}, {0, 3}},
      {{0, 1}, {0, 0}}, {{0, 2}, {0, 1}}, {{1, 1}, {0, 1}}, {{0, 3}, {0, 2}}};
  const Graph graph{.nodes = nodes, .edges = edges};

  BreadthFirstSearch bfs{graph};

  const Node start{0, 0};
  const Node goal{0, 3};
  std::optional<std::vector<Node>> path{bfs.getPath(start, goal)};

  if (!path.has_value()) {
    std::cout << "Path is empty\n";
    did_a_test_fail = true;
  } else {
    const std::vector<Node> expected_path{{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    if (expected_path != path.value()) {
      std::cout << "The path does not match the expected path.\n";
      std::cout << "  Expected path: ";
      for (const Node &node : expected_path) {
        std::cout << "(" << node.first << ", " << node.second << ") ";
      }
      std::cout << std::endl;

      std::cout << "  Path: ";
      for (const Node &node : path.value()) {
        std::cout << "(" << node.first << ", " << node.second << ") ";
      }
      std::cout << std::endl;

      did_a_test_fail = true;
    }
  }

  return did_a_test_fail;
}

int main(void) {
  const std::string test_suite_name{"Test Breadth First Search"};
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
    const std::string test_name{"test_getPath"};
    const bool is_test_a_failure = test_getPath();
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