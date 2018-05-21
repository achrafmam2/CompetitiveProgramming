#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct DataCenter {
  int n;
  vector<vector<int>> graph;

  DataCenter(vector<vector<int>> graph) {
    n = (int)graph.size();
    this->graph = graph;
  }

  vector<int> order;
  vector<bool> seen;

  void dfs(int s) {
    seen[s] = true;
    for (int v : graph[s]) {
      if (!seen[v]) {
        dfs(v);
      }
    }
    order.push_back(s);
  }

  vector<int> find() {
    seen.resize(n);
    seen.assign(n, false);
    for (int s = 0; s < n; s++) {
      if (!seen[s]) {
        dfs(s);
      }
    }

    vector<vector<int>> rev(n);
    for (int u = 0; u < n; u++) {
      for (int v : graph[u]) {
        rev[v].push_back(u);
      }
    }

    const int inf = (int)1e9;

    int m = 0;
    vector<int> id(n, -1);
    vector<int> count(n, 0);
    seen.assign(n, false);
    while (!order.empty()) {
      int s = order.back(); order.pop_back();
      if (seen[s]) {
        continue;
      }
      queue<int> q;
      q.push(s);
      seen[s] = true;
      id[s] = m;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        count[m]++;
        for (int v : rev[u]) {
          if (!seen[v]) {
            seen[v] = true;
            id[v] = m;
            q.push(v);
          } else if (m != id[v]) {
            count[m] = inf;
          }
        }
      }
      m++;
    }

    int best = inf;
    int start = -1;
    for (int u = 0; u < n; u++) {
      if (count[id[u]] < best) {
        best = count[id[u]];
        start = u;
      }
    }

    vector<int> sol;
    queue<int> q;
    seen.assign(n, false);
    q.push(start);
    seen[start] = true;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      sol.push_back(u);
      for (int v : rev[u]) {
        if (!seen[v]) {
          seen[v] = true;
          q.push(v);
        }
      }
    }

    return sol;
  }
};

int main(void) {
  int n, m, h;
  scanf("%i %i %i", &n, &m, &h);

  vector<int> maintenances(n);
  for (int &e : maintenances) {
    scanf("%i", &e);
  }

  vector<vector<int>> t(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%i %i", &u, &v);
    u--, v--;
    if ((maintenances[u] + 1) % h == maintenances[v]) {
      t[v].push_back(u);
    }
    if ((maintenances[v] + 1) % h == maintenances[u]) {
      t[u].push_back(v);
    }
  }

  auto ans = DataCenter(t).find();
  printf("%i\n", (int)ans.size());
  for (int e : ans) {
    printf("%i ", e + 1);
  }
  puts("");

  return 0;
}

