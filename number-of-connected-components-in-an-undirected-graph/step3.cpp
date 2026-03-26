#include <vector>
class Solution {
 public:
  int countComponents(int n, std::vector<std::vector<int>>& edges) {
    int components_count = 0;
    std::vector<std::vector<int>> node_to_neibors(n);
    for (const auto& edge : edges) {
      int node1 = edge[0];
      int node2 = edge[1];
      node_to_neibors[node1].push_back(node2);
      node_to_neibors[node2].push_back(node1);
    }
    std::vector<int> visited(n, false);
    for (int node = 0; node < n; ++node) {
      if (!visited[node]) {
        ++components_count;
        VisitConnectedNodes(node, node_to_neibors, visited);
      }
    }
    return components_count;
  }

 private:
  void VisitConnectedNodes(int node,
                           const std::vector<std::vector<int>>& node_to_neibors,
                           std::vector<int>& visited) {
    visited[node] = true;
    for (auto neibor_node : node_to_neibors[node]) {
      if (!visited[neibor_node]) {
        VisitConnectedNodes(neibor_node, node_to_neibors, visited);
      }
    }
  }
};
