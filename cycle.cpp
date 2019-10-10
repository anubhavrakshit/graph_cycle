#include <iostream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::pair;
using std::unordered_set;

bool explore(vector<vector<int> > &adj, unordered_set<int> &black, unordered_set<int> &gray, int v) {
    bool ret = false;
    std::cout << "Exploring " << v + 1 << std::endl;
    if (!black.count(v)) {
        if (!gray.count(v)) {
            gray.insert(v);
        } else {
               return true;
        }

        //std::cout << "Insert" << v + 1 << std::endl;
        vector<int> nbrs = adj[v];
        for (auto v: nbrs) {
           ret = explore(adj, black, gray, v);
           if (ret) {
               return true;
           }
        }
        gray.erase(v);
        black.insert(v);
    }
    return ret;
}

// Gray Set for currently exploring
// Black Set for completed exploring
// If vertex is being explored and we see it in gray then its a cycle.
int acyclic(vector<vector<int> > &adj) {
  //write your code here
  unordered_set <int> black;
  unordered_set <int> gray;

  for (int i = 0; i < adj.size(); i++) {
      std::cout << "Explore Start " << i + 1 << std::endl;
      bool is_cyclic = explore(adj, black, gray, i);
      if (is_cyclic) {
          return 1;
      }
  }

  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  std::cout << acyclic(adj);
}
