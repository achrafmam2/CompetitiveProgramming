#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(void) {
  int k;
  scanf("%i", &k);

  vector<int> a(k);
  for (int &e : a) {
    scanf("%i", &e);
  }

  const int N = int(1e7);

  vector<bool> is_prime(N + 1, true);
  vector<int> divisor(N + 1);

  for (int i = 2; i <= N; i++) {
    if (is_prime[i]) {
      divisor[i] = i;
      for (long long j = i + i; j <= N; j += i) {
        is_prime[j] = false;
        divisor[j] = i;
      }
    }
  }

  vector<long long> take(N + 1);
  for (int e : a) {
    take[e]++;
  }

  vector<long long> exponent(N + 1);
  for (int i = N; i > 1; i--) {
    int num = i;
    while (num > 1) {
      exponent[divisor[num]] += take[i];
      num /= divisor[num];
    }
    take[i - 1] += take[i];
  }

  map<int, long long> factors;
  for (int i = 2; i <= N; i++) {
    if (exponent[i] > 0) {
      factors[i] = exponent[i];
    }
  }

  long long lo = 1, hi = (long long)1e15, ans = -1;
  while (lo <= hi) {
    long long mid = (lo + hi) / 2;

    bool can = true;
    for (auto node : factors) {
      int p = node.first;
      long long req = node.second;

      long long has = 0, tmp = mid;
      while (tmp > 1) {
        has += tmp / p;
        tmp /= p;
      }

      if (has < req) {
        can = false;
        break;
      }
    }

    if (can) {
      ans = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  printf("%lld\n", ans);

  return 0;
}

