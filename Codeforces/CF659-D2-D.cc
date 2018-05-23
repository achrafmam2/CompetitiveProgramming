#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(void) {
  int n;
  scanf("%i", &n);

  vector<pair<int, int>> points(n + 1);
  for (auto &p : points) {
    scanf("%i %i", &p.first, &p.second);
  }

  enum { TOP, BOTTOM, LEFT, RIGHT };

  set<pair<int, int>> valid;
  valid.insert(make_pair(TOP, LEFT));
  valid.insert(make_pair(BOTTOM, RIGHT));
  valid.insert(make_pair(LEFT, BOTTOM));
  valid.insert(make_pair(RIGHT, TOP));

  int count = 0, old = TOP;
  for (int i = 1; i < n; i++) {
    int cur;
    if (points[i].first == points[i + 1].first) {
      if (points[i].second < points[i + 1].second) {
        cur = TOP;
      } else {
        cur = BOTTOM;
      }
    } else {
      if (points[i].first < points[i + 1].first) {
        cur = RIGHT;
      } else {
        cur = LEFT;
      }
    }
    count += valid.count(make_pair(old, cur));
    old = cur;
  }

  printf("%i\n", count);

  return 0;
}

