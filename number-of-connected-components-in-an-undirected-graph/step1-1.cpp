#include <list>
#include <stack>
#include <vector>

using Edge = std::vector<int>;
class Solution {
 public:
  int countComponents(int n, std::vector<Edge>& edges) {
    std::list<Edge> edges_store(edges.begin(), edges.end());
    int count_components = 0;
    while (!edges_store.empty()) {
      ++count_components;
      auto first_edge = std::move(edges_store.front());
      edges_store.pop_front();
      std::stack<int> connected_nodes;
      connected_nodes.push(first_edge[0]);
      connected_nodes.push(first_edge[1]);
      while (!connected_nodes.empty()) {
        auto base_node = std::move(connected_nodes.top());
        connected_nodes.pop();
        for (auto itr = edges_store.begin(); itr != edges_store.end();) {
          Edge& edge = *itr;
          bool connected = pushIfConnected(connected_nodes, base_node, edge);
          if (connected) {
            itr = edges_store.erase(itr);
          } else {
            itr++;
          }
        }
      }
    }
    return count_components;
  }

 private:
  // return 'true' if connected
  bool pushIfConnected(std::stack<int>& nodes, int base_node,
                       const Edge& edge) {
    if (base_node == edge[0]) {
      nodes.push(edge[1]);
      return true;
    }
    if (base_node == edge[1]) {
      nodes.push(edge[0]);
      return true;
    }
    return false;
  }
  bool HasConnected(int base_node, const Edge& edge) {
    return base_node == edge[0] || base_node == edge[1];
  }
};
