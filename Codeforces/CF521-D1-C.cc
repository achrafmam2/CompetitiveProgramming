#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = (int)1e9 + 7;

long long binpow(long long a, long long b) {
  long long ret = 1;
  while (b > 0) {
    if (b % 2) {
      ret = (ret * a) % mod;
    }
    b /= 2;
    a = (a * a) % mod;
  }
  return ret;
}

int main(void) {
  int n, k;
  scanf("%i %i", &n, &k);

  vector<char> digits(n + 1);
  scanf("%s", &digits[0]);

  if (k == 0) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
      ans = (ans * 10) + (digits[i] - '0');
      ans %= mod;
    }
    printf("%lld\n", ans);

    return 0;
  }

  vector<long long> factorial(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    factorial[i] = factorial[i - 1] * i % mod;
  }

  auto choose = [&](long long n, long long k) -> long long {
    return factorial[n] * binpow(factorial[k], mod - 2) % mod * binpow(factorial[n - k], mod - 2) % mod;
  };

  vector<long long> ways(n - k + 1);
  for (int i = 1; i <= n - k; i++) {
    ways[i] = binpow(10, i - 1) * choose(n - 1 - i, k - 1) % mod;
  }

  for (int i = 1; i <= n - k; i++) {
    ways[i] += ways[i - 1];
    ways[i] %= mod;
  }

  long long ans = 0;
  int r = n - 1;
  for (int i = n - 1; i >= 0; i--) {
    while ((n - 1) - (r - i) - k < 0) {
      r--;
    }

    long long add = 0;
    int len = r - i + 1;
    if (r == n - 1) {
      if (len >= 2) {
        add = ways[len - 1];
      }
      add += binpow(10, len - 1) * choose(i, k) % mod;
    } else {
      add = ways[len];
    }

    ans += add * (digits[i] - '0') % mod;
    ans %= mod;
  }

  printf("%lld\n", ans);

  return 0;
}

