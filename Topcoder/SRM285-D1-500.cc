#include <algorithm>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

class RobotTesting {
public:
  int N;
  string program;
  int dp[1001][1001];

  int dfs(int x, int y) {
    int &ret = dp[x][y];

    if (ret == -1) {
      ret = 0;
      int ox = x, oy = y;
      for (int c : program) {
        ret++;
        switch (c) {
          case 'U':
            ox--;
            break;
          case 'D':
            ox++;
            break;
          case 'L':
            oy--;
            break;
          case 'R':
            oy++;
        }
        if (ox < 0 || ox >= N || oy < 0 || oy >= N) {
          return ret;
        }
      }
      if (ox == x && oy == y) {
        ret = 50000;
      } else {
        ret = ret + dfs(ox, oy);
      }
    }

    return ret;
  }

  double estimateCommands(int N, string program) {
    this->program = program;
    this->N = N;

    memset(dp, -1, sizeof(dp));

    long long count = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        count += dfs(i, j);
      }
    }

    return count / double(N * N);
  }
};
