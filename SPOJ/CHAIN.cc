/// CHAIN
/// For each component keep 2 extra information: who it can eat (denoted by `Next`),
/// and who can it (denoted by `Prev`). Merging two components should update `Next`, and
/// `Prev` accordingly.

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 50001;

int id[3 * N];
int Next[3 * N];
int Prev[3 * N];

void init(int n) {
  for (int i = 0; i < 3 * n; i++) {
    id[i] = i;
    Next[i] = (i + n) % (3 * n);
    Prev[i] = (i + 2 * n) % (3 * n);
  }
}

int get(int x) {
  if (id[x] != x) {
    id[x] = get(id[x]);
  }
  return id[x];
}

void merge(int x, int y) {
  x = get(x);
  y = get(y);
  if (x != y) {
    id[y] = x;
  }
}

void mergeAll(int x, int y) {
  merge(x, y);
  merge(Next[x], Next[y]);
  merge(Prev[x], Prev[y]);
}

bool eq(int x, int y) {
  return get(x) == get(y);
}

bool same(int x, int y) {
  if (eq(Next[x], y) || eq(Prev[x], y)) {
    return false;
  }
  mergeAll(x, y);
  return true;
}

bool eat(int x, int y) {
  return same(x, Prev[y]);
}

int main(void) {
  int T;
  scanf("%i", &T);

  while (T--) {
    int n, k;
    scanf("%i %i", &n, &k);

    init(n);

    int count = 0;
    while (k--) {
      int type, x, y;
      scanf("%i %i %i", &type, &x, &y);

      x--, y--;

      if (x >= n || y >= n) {
        count++;
        continue;
      }

      switch (type) {
        case 1:
          if (!same(x, y)) count++;
          break;
        case 2:
          if (!eat(x, y)) count++;
          break;
      }
    }

    printf("%i\n", count);
  }

  return 0;
}
