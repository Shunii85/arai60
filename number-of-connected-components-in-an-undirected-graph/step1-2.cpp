#include <vector>
class Solution {
 public:
  int countComponents(int n, std::vector<std::vector<int>>& edges) {
    int res = 0;
    std::vector<std::vector<int>> adj(n);
    for (const auto& edge : edges) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }
    std::vector<bool> visited(n, false);
    for (int node = 0; node < n; ++node) {
      if (!visited[node]) {
        dfs(adj, visited, node);
        ++res;
      }
    }
    return res;
  }

 private:
  void dfs(std::vector<std::vector<int>>& adj, std::vector<bool>& visited,
           int node) {
    visited[node] = true;
    for (auto nei : adj[node]) {
      if (!visited[nei]) {
        dfs(adj, visited, nei);
      }
    }
  }
};
