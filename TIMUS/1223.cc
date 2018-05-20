/// Chernobyl’ Eagle on a Roof
/// Notice that the optimal number of experiments don't get better if we have more than
/// `ceil(log_2(n)) + 1` — by using a binary search strategy.
/// We calculate the optimal number of experiments using the reccurence:
///                         | 0, if height = 0
///     F(height, #eggs) =  | infinity, #eggs = 0 AND height > 0
///                         | min(max(F(h, #eggs - 1), F(height - h, #eggs))), for 1 <= h <= height

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1000;
const int M = 50;
const int inf = 100000000;

int f[N + 1][M + 1];

int main(void) {
  for (int i = 0; i <= M; i++) {
    f[0][i] = 0;
  }

  for (int i = 1; i <= N; i++) {
    f[i][0] = inf;
  }

  for (int h = 1; h <= N; h++) {
    for (int i = 1; i <= M; i++) {
      f[h][i] = inf;
      for (int j = 1; j <= h; j++) {
        f[h][i] = min(f[h][i], max(f[j - 1][i - 1], f[h - j][i]) + 1);
      }
    }
  }

  int n, h;
  while (scanf("%i %i", &n, &h)) {
    if (!n && !h) {
      break;
    }
    printf("%i\n", f[h][min(n, M)]);
  }

  return 0;
}
