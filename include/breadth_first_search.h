#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "types.h"

using Node = Coordinate<size_t>;
using Edge = std::pair<Node, Node>;

struct Graph {
  std::vector<Node> nodes;
  std::vector<Edge> edges;
};

struct PathNode {
  Node node;
  std::shared_ptr<PathNode> parent;
};

class BreadthFirstSearch {
public:
  BreadthFirstSearch(const Graph &graph);

  std::optional<std::vector<Node>> getPath(const Node &start, const Node &goal) const;

private:
  std::vector<Node> getNeighbors(const Node &node) const;
  bool isValidNode(const Node &node) const;

  Graph graph_;
};

#endif // BREADTH_FIRST_SEARCH_H
