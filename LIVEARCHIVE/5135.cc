#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Mining {
  vector<vector<int>> graph;
  vector<bool> is_cutpoint, seen;
  vector<int> entry, low, count;

  int n = 0, timer;
  int ans = 0;
  long long ways = 1;

  Mining(int m) {
    vector<int> from(m), to(m);

    for (int i = 0; i < m; i++) {
      scanf("%i %i", &from[i], &to[i]);
      n = max(n, from[i]);
      n = max(n, to[i]);
    }

    graph.resize(n + 1);
    is_cutpoint.resize(n + 1);
    seen.resize(n + 1);
    entry.resize(n + 1);
    low.resize(n + 1);
    count.resize(n + 1);

    for (int i = 0; i < m; i++) {
      graph[from[i]].push_back(to[i]);
      graph[to[i]].push_back(from[i]);
    }
  }

  void init() {
    timer = 0;
    fill(begin(seen), end(seen), false);
    fill(begin(is_cutpoint), end(is_cutpoint), false);
    fill(begin(low), end(low), 0);
    fill(begin(entry), end(entry), 0);
  }

  bool calc(int s, int p = -1) {
    bool contains = false;

    count[s] = 1;
    seen[s] = true;
    entry[s] = low[s] = timer++;
    for (int v : graph[s]) {
      if (v == p) {
        continue;
      } else if (!seen[v]) {
        bool has = calc(v, s);
        contains = contains || has;
        count[s] += count[v];
        low[s] = min(low[s], low[v]);
        if (entry[s] <= low[v]) {
          contains = true;
          if (!has) {
            ans++;
            ways = ways * (long long)count[v];
          }
        }
      } else {
        low[s] = min(low[s], entry[v]);
      }
    }

    return contains;
  }

  void dfs(int s, int p = -1) {
    seen[s] = true;
    entry[s] = low[s] = timer++;
    int children = 0;
    for (int v : graph[s]) {
      if (v == p) {
        continue;
      } else if (!seen[v]) {
        dfs(v, s);
        low[s] = min(low[s], low[v]);
        if (p != -1 && entry[s] <= low[v]) {
          is_cutpoint[s] = true;
        }
        children++;
      } else {
        low[s] = min(low[s], entry[v]);
      }
    }
    if (p == -1 && children > 1) {
      is_cutpoint[s] = true;
    }
  }

  void find_cutpoints() {
    init();
    dfs(1);
  }

  pair<int, long long> theCount() {
    find_cutpoints();

    bool found = false;
    int start = -1;
    for (int i = 1; i <= n; i++) {
      if (is_cutpoint[i]) {
        found = true;
        start = i;
      }
    }

    if (!found) {
      return make_pair(2, (long long)n * (n - 1) / 2);
    }

    init();
    calc(start);

    return make_pair(ans, ways);
  }
};

int main(void) {
  int t = 1;
  int m;
  while (scanf("%i", &m)) {
    if (!m) {
      break;
    }
    auto ans = Mining(m).theCount();
    printf("Case %i: %i %lld\n", t++, ans.first, ans.second);
  }
  return 0;
}

