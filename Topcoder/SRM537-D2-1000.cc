#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class PrinceXToastbook {
public:
  double eat(vector <int> prerequisite) {
    int n = (int)prerequisite.size();

    vector<vector<int>> tree(n);
    vector<int> in(n);
    for (int i = 0; i < n; i++) {
      if (prerequisite[i] >= 0) {
        tree[prerequisite[i]].push_back(i);
        in[i]++;
      }
    }

    vector<int> num_parents(n);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (in[i] == 0) {
        q.push(i);
      }
    }

    vector<double> factorial(n + 1, 1.0);
    for (int i = 1; i <= n; i++) {
      factorial[i] = factorial[i - 1] * i;
    }

    double ans = 0.0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      ans += 1 / factorial[num_parents[u] + 1];
      for (int v : tree[u]) {
        if (--in[v] == 0) {
          q.push(v);
          num_parents[v] = num_parents[u] + 1;
        }
      }
    }

    return ans;
  }
};
