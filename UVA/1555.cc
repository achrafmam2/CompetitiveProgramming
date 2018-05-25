/// Garland.
/// [very brief solution sketch]
/// Notice that:
///     `H_i = (H_{i-x} + H_{i+x})/2 - x^2` for (i-x) >= 1 AND (i+x) <= n.
/// This means that if we have `H_{n} = B`, then, we can calculate `H_{n/2}` using the
/// formula above. (NOTE: in case `n` is even keep expanding the formula)
/// Recursively we calculate the other points. In case we get some `H_{m} < 0` then it is
/// not possible.
/// With this in mind we can do a binary search on `B`, and pick the best one.
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool can(double A, double B, int n) {
  if (n <= 2) {
    return true;
  }

  if (n % 2) {
    int m = (n + 1) / 2;
    double hm = (A + B) / 2 - (m - 1) * (m - 1);
    if (hm < 0.0) {
      return false;
    }
    return can(A, hm, m) && can(hm, B, m);
  } else {
    int m = n / 2;
    double hm = A / 2 - (m - 1) * (m - 1);
    int idx = n - 1;
    double div = 4;
    for (int i = 0; i < 64; i++) {
      if (idx < n / 2) {
        hm += (A - 2 * (idx - 1) * (idx - 1)) / div;
        idx = 2 * idx - 1;
      } else {
        hm += (B - 2 * (n - idx) * (n - idx)) / div;
        idx = 2 * idx - n;
      }
      if (idx == m) {
        hm *= div / (div - 1);
        break;
      }
      div *= 2.0;
    }
    if (hm < 0.0) {
      return false;
    }
    return can(A, hm, m) && can(hm, B, m + 1);
  }
}

int main(void) {
  int n;
  double A;
  while (scanf("%i %lf", &n, &A) != EOF) {
    int rep = 64;
    double lo = 0.0, hi = 1e15, ans = -1;
    while (rep--) {
      double mid = (lo + hi) / 2.0;
      if (can(A, mid, n)) {
        ans = mid;
        hi = mid;
      } else {
        lo = mid;
      }
    }
    printf("%.2f\n", ans);
  }

  return 0;
}
