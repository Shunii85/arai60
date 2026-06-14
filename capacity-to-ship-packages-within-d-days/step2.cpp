#include <algorithm>
#include <numeric>
#include <vector>
class Solution {
 public:
  int shipWithinDays(const std::vector<int>& packages, int days) {
    int low_capacity = *std::max_element(packages.begin(), packages.end());
    int high_capacity = std::accumulate(packages.begin(), packages.end(), 0);
    int min_capacity = 0;
    while (low_capacity <= high_capacity) {
      int capacity = low_capacity + (high_capacity - low_capacity) / 2;
      if (ShipDays(packages, capacity) <= days) {
        min_capacity = capacity;
        high_capacity = capacity - 1;
      } else {
        low_capacity = capacity + 1;
      }
    }
    return min_capacity;
  }

 private:
  int ShipDays(const std::vector<int>& packages, int ship_capacity) {
    int days_needed = 0;
    int package_group_weight = 0;
    for (const auto weight : packages) {
      if (package_group_weight + weight > ship_capacity) {
        ++days_needed;
        package_group_weight = 0;
      }
      package_group_weight += weight;
    }
    return ++days_needed;
  }
};
