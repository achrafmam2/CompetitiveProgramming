#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N = 111;

const long long inf = (long long)1e14;
long long w[N + 1][N + 1];

int main(void) {
  int n, d;
  scanf("%i %i", &n, &d);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      w[i][j] = inf;
    }
  }

  vector<int> a(n + 1);
  for (int i = 2; i <= n - 1; i++) {
    scanf("%i", &a[i]);
  }

  vector<int> X(n + 1), Y(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%i %i", &X[i], &Y[i]);
  }

  for (int i = 1; i <= n; i++) {
    w[i][i] = 0;
    for (int j = 1; j <= n; j++) {
      if (i != j) {
        w[i][j] = (abs(X[i] - X[j]) + abs(Y[i] - Y[j])) * d - a[j];
      }
    }
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
      }
    }
  }

  printf("%lld\n", w[1][n]);

  return 0;
}
