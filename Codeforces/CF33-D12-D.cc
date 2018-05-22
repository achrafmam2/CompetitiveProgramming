#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

struct Circle {
  int x, y;
  long long radi;
  Circle() {}
  Circle(int x, int y, long long radi) {
    this->x = x;
    this->y = y;
    this->radi = radi;
  }
};

int main(void) {
  int n, m, k;
  scanf("%i %i %i", &n, &m, &k);

  vector<int> X(n), Y(n);
  for (int i = 0; i < n; i++) {
    scanf("%i %i", &X[i], &Y[i]);
  }

  vector<Circle> circles(m);
  for (Circle &c : circles) {
    scanf("%lld %i %i", &c.radi, &c.x, &c.y);
  }
  circles.push_back(Circle(0, 0, static_cast<long long>(1e13)));

  sort(begin(circles), end(circles), [](Circle a, Circle b) {
    return a.radi < b.radi;
  });

  auto distance = [](Circle a, Circle b) -> double {
    return hypot(a.x - b.x, a.y - b.y);
  };

  vector<vector<int>> tree(m + 1);
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m + 1; j++) {
      if (distance(circles[i], circles[j]) < circles[j].radi) {
        tree[j].push_back(i);
        tree[i].push_back(j);
        break;
      }
    }
  }

  vector<int> which(n, -1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m + 1; j++) {
      if (hypot(X[i] - circles[j].x, Y[i] - circles[j].y) < circles[j].radi) {
        which[i] = j;
        break;
      }
    }
  }

  vector<vector<int>> distances(m + 1);
  for (int i = 0; i < m + 1; i++) {
    vector<bool> seen(m + 1);
    vector<int> d(m + 1);
    queue<int> q;
    q.push(i);
    seen[i] = true;
    d[i] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : tree[u]) {
        if (!seen[v]) {
          seen[v] = true;
          d[v] = 1 + d[u];
          q.push(v);
        }
      }
    }
    distances[i] = d;
  }

  while (k--) {
    int a, b;
    scanf("%i %i", &a, &b);
    printf("%i\n", distances[which[a - 1]][which[b - 1]]);
  }

  return 0;
}

