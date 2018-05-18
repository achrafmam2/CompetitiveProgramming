/// Context Advertising
/// Let f[i][j] = number of words to fit in 2^j lines.
/// We have f[i][j] = f[i][j - 1] + f[i + f[i][j - 1]][j - 1], for j > 0;
/// Let t[i] = number of words to fit in `m` lines. We can use `f` to calculate the `t[i]`s.

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

const int N = 1000010;
const int M = 22;

int f[N][M];

int main(void) {
  int n, m, c;
  cin >> n >> m >> c;

  vector<string> words(n);
  for (string &word : words) {
    cin >> word;
  }

  int r = n - 1;
  int sum = 0;
  for (int i = n - 1; i >= 0; i--) {
    sum += (int)words[i].size();
    while (sum + r - i > c) {
      sum -= (int)words[r].size();
      r--;
    }
    f[i][0] = r - i + 1;
  }

  for (int j = 1; (1 << j) <= m; j++) {
    for (int i = 0; i < n; i++) {
      f[i][j] = f[i][j - 1] + f[i + f[i][j - 1]][j - 1];
    }
  }

  vector<int> t(n);
  for (int i = 0; i < n; i++) {
    int idx = i;
    for (int j = 0; j < M; j++) {
      if (m & (1 << j)) {
        t[i] += f[idx][j];
        idx += f[idx][j];
      }
    }
  }

  int best = 0, s = 0;
  for (int i = 0; i < n; i++) {
    if (t[i] > best) {
      best = t[i];
      s = i;
    }
  }

  for (int l = 0; l < m; l++) {
    if (words[s].size() > c) {
      break;
    }
    int count = f[s][0];
    for (int i = 0; i < count; i++) {
      cout << words[i + s];
      cout << ((i + 1 < count) ? " " : "\n");
    }
    s += count;
  }

  return 0;
}

