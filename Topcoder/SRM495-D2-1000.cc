#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

class HexagonPuzzle {
public:
  const int mod = (int)1e9 + 7;

  int theCount(vector<string> board) {
    int n = int(board.size());

    vector<vector<bool>> seen;
    for (int i = 0; i < n; i++) {
      seen.push_back(vector<bool>(i + 1));
    }

    vector<long long> factorial(n * n + 1);

    factorial[1] = factorial[2] = 1;
    for (int i = 3; i <= n * n; i++) {
      factorial[i] = factorial[i - 1] * i % mod;
    }

    auto is_ok = [&](int x, int y) -> bool {
      return (x < n) && (x >= 0) && (y >= 0) && (y < x + 1) && board[x][y] == '.';
    };

    queue<int> q;

    auto add = [&](int x, int y) -> int {
      if (seen[x][y]) {
        return 0;
      }
      seen[x][y] = true;
      q.push(x);
      q.push(y);
      return 1;
    };

    long long ans = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i + 1; j++) {
        if (seen[i][j] || board[i][j] == 'X') {
          continue;
        }

        int count = add(i, j);

        int dx[] = {0, -1, -1, 0, 1, 1};
        int dy[] = {-1, -1, 0, 1, 1, 0};

        while (!q.empty()) {
          int x = q.front(); q.pop();
          int y = q.front(); q.pop();

          for (int k = 0; k < 6; k++) {
            int a[] = {x + dx[k], y + dy[k]};
            int b[] = {x + dx[(k + 5) % 6], y + dy[(k + 5) % 6]};

            if (is_ok(a[0], a[1]) && is_ok(b[0], b[1])) {
              count += add(a[0], a[1]);
              count += add(b[0], b[1]);
            }
          }
        }

        ans = (ans * factorial[count]) % mod;
      }
    }

    return (int)ans;
  }
};

