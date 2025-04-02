#include "breadth_first_search.h"

#include <algorithm>
#include <optional>
#include <queue>
#include <vector>

BreadthFirstSearch::BreadthFirstSearch(const Graph &graph) : graph_{graph} {}

std::optional<std::vector<Node>>
BreadthFirstSearch::getPath(const Node &start, const Node &goal) const {
  std::deque<PathNode> open_list{};
  std::deque<Node> closed_list{};

  if (!isValidNode(start) || !isValidNode(goal)) {
    // TODO: return error
    return std::nullopt;
  }

  open_list.emplace_back(PathNode{.node = start, .parent = nullptr});
  while (open_list.size()) {
    const PathNode active_node = open_list.front();
    open_list.pop_front();

    // Expand the node
    std::vector<Node> neighbors = getNeighbors(active_node.node);

    // Add neighbors not in closed list to open list
    for (const Node &neighbor : neighbors) {
      if (neighbor == goal) {
        std::vector<Node> path{ goal, active_node.node};
        std::shared_ptr<PathNode> path_node_ptr = active_node.parent;
        while (path_node_ptr != nullptr) {
          path.emplace_back(path_node_ptr->node);
          path_node_ptr = path_node_ptr->parent;
        }

        std::reverse(path.begin(), path.end());
        return path;
      }

      auto it = std::find(closed_list.cbegin(), closed_list.cend(), neighbor);
      if (it == closed_list.cend()) {
        // Node is not in the closed list
        open_list.emplace_back(
            PathNode{.node = neighbor,
                     .parent = std::make_shared<PathNode>(active_node)});
      }
    }

    closed_list.emplace_back(active_node.node);
  }

  // TODO: return error, path not found
  return std::nullopt;
}

std::vector<Node> BreadthFirstSearch::getNeighbors(const Node &node) const {
  std::vector<Edge> relavent_edges{};
  std::copy_if(graph_.edges.cbegin(), graph_.edges.cend(),
               std::back_inserter(relavent_edges),
               [node](const Edge &edge) { return node == edge.first; });

  std::vector<Node> neighbors;
  neighbors.reserve(relavent_edges.size());
  for (const Edge &edge : relavent_edges) {
    neighbors.emplace_back(edge.second);
  }

  return neighbors;
}

bool BreadthFirstSearch::isValidNode(const Node &node) const {
  auto it = std::find(graph_.nodes.cbegin(), graph_.nodes.cend(), node);
  if (it == graph_.nodes.cend()) {
    // The node does not exist
    return false;
  }

  return true;
}