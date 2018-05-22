/// Eefun Plays LOL
/// With `k` eggs and `n` experiments we can cover at most `Σ (n Choose i) [1 <= i <= k]`
/// floors. Hence, the optimal number of experiments is the minimum `n` such that
/// `Σ (n Choose i) [1 <= i <= k]` >= `Height of the Building`. We can find such `n`
/// using binary search.
/// Note that if `k` >= `ceil(log_2{Height})` we can use a binary search strategy,
/// thus the required number of experiments is `ceil(log_2{Height})`.
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef unsigned long long uint64;

const int N = 64;
vector<int> factors[N + 1];

vector<int> factorize(int n) {
  vector<int> factors;
  for (int d = 2; d * d <= n; d++) {
    while (n % d == 0) {
      n /= d;
      factors.push_back(d);
    }
  }
  if (n > 1) factors.push_back(n);
  return factors;
}

inline uint64 sum_binomial(uint64 n, int k, uint64 threshold) {
  uint64 ret = 0, binom = 1;
  for (int i = 0; i < k; i++) {
    uint64 m = (n - i);
    if (m == 0) { break; }
    for (int d : factors[i + 1]) {
      if (m % d == 0) {
        m /= d;
      } else {
        binom /= d;
      }
    }
    if (binom > threshold / m) {
      return threshold;
    }
    binom *= m;
    ret += binom;
    if (ret >= threshold) {
      return threshold;
    }
  }
  return ret;
}

inline uint64 theCount(uint64 n, uint64 k) {
  if (k == 1) {
    return n;
  }

  int count = 0;
  uint64 tmp = n;
  while (tmp > 0) {
    tmp = tmp / 2;
    count++;
  }

  if (count <= k) {
    return count;
  }

  uint64 lo = 1, hi = (uint64)2e9, ans = 0;
  while (lo <= hi) {
    uint64 mid = (lo + hi) / 2;
    if (sum_binomial(mid, k, n) >= n) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  return ans;
}

int main(void) {
  int T;
  scanf("%i", &T);

  for (int i = 1; i <= N; i++) {
    factors[i] = factorize(i);
  }

  while (T--) {
    uint64 n, h;
    scanf("%llu %llu", &n, &h);
    printf("%llu\n", theCount(n, h));
  }

  return 0;
}
