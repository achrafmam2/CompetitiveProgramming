/// Lining up
/// For each pair of points (`p`, `q`) where `p` is on the left of `q`, add a directed
/// edge (`p` to `q`) with weight equal to their slope.
/// Note that points in the same line have the same slope between each other.
/// For each point follow the edges with same slope.
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int gcd(int a, int b) {
  if (!b) return a;
  return gcd(b, a % b);
}

int main(void) {
  int T;
  scanf("%i\n\n", &T);

  for (int t = 1; t <= T; t++) {
    char s[100];
    vector<pair<int, int>> points;
    while (gets(s) && strlen(s) > 0) {
      int x, y;
      sscanf(s, "%i %i", &x, &y);
      points.push_back(make_pair(x, y));
    }

    sort(begin(points), end(points));

    int n = (int)points.size();

    vector<map<pair<int, int>, int>> next(n);
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int dy = points[j].second - points[i].second;
        int dx = points[j].first - points[i].first;
        int d = gcd(dx, dy);
        auto slope = make_pair(dx / d, dy / d);
        if (!next[i].count(slope)) {
          next[i][slope] = j;
        }
      }
    }

    int best = 0;
    for (int i = 0; i < n; i++) {
      for (auto node : next[i]) {
        auto slope = node.first;
        int cur = i;
        int count = 1;
        while (next[cur].count(slope)) {
          count++;
          int last = cur;
          cur = next[cur][slope];
          if (last != i) next[last].erase(slope);
        }
        best = max(best, count);
      }
    }

    if (t > 1) puts("");
    printf("%i\n", best);
  }

  return 0;
}
