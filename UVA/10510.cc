/// Cactus
/// Partition the graph using articulation points (the term partition is losely used here,
/// because the partitions can intersect in one vertex which must be an articulation point).
/// For each partition, it should be a simple cycle.

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Cactus {
  vector<vector<int>> graph;
  vector<int> low, entry;
  vector<int> seen, processed;
  int internal_clock;
  int n, m;

  Cactus() {
    scanf("%i %i", &n, &m);

    graph.resize(n);

    low.resize(n);
    entry.resize(n);

    seen.resize(n);
    processed.resize(n);

    internal_clock = 0;

    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%i %i", &u, &v);
      graph[u].push_back(v);
    }
  }

  bool is_cactus() {
    bool is_ok =  dfs(0);
    // Check that the graph is connected.
    for (int i = 0; i < n; i++) {
      if (!seen[i]) {
        return false;
      }
    }
    return is_ok;
  }

  /// If there is a simple and unique path from v to s.
  bool is_simple(int v, int s) {
    if (v == s) {
      return true;
    }

    int count = 0;
    for (int next : graph[v]) {
      // Check if in same partition -- must have  same low index or is the end of the cycle.
      if (next == s || low[next] == entry[s]) {
        count++;
      }
    }

    if (count > 1) {
      return false;
    }

    for (int next : graph[v]) {
      if (next == s || low[next] == entry[s]) {
        return is_simple(next, s);
      }
    }

    return false;
  }

  bool dfs(int s) {
    seen[s] = true;
    entry[s] = low[s] = internal_clock++;

    for (int v : graph[s]) {
      if (!seen[v]) {
        if (!dfs(v)) {
          return false;
        }

        low[s] = min(low[s], low[v]);

        if (low[v] > entry[s]) {
          // Not strongly connected.
          return false;
        }

        if (low[v] == entry[s]) {
          // Can partition at vertex s.
          if (!is_simple(v, s)) {
            return false;
          }
        }
      } else {
        if (processed[v]) {
          // Complex cycle detected.
          return false;
        }
        low[s] = min(low[s], entry[v]);
      }
    }

    processed[s] = true;

    return true;
  }
};

int main(void) {
  int T;
  scanf("%i", &T);

  while (T--) {
    auto cactus = Cactus();
    puts(cactus.is_cactus() ? "YES" : "NO");
  }

  return 0;
}

