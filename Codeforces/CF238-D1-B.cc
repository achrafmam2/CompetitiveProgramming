/// Boring Partition
/// Sort input sequence S.
/// For each index `i` we consider the two partitions (0 to i) and (i + 1, |S| - 1).
/// Among all possible partitions we choose the one that yields the best answer.

#include <cstdio>
#include <deque>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int calc(deque<int> &A, deque<int> &B, int h) {
  const int inf = (int)1e9 + 7;

  int n = (int)A.size();
  int m = (int)B.size();

  int maxi = (n && m) ? A[n - 1] + B[m - 1] + h : 0;
  if (n > 1) {
    maxi = max(maxi, A[n - 1] + A[n - 2]);
  }
  if (m > 1) {
    maxi = max(maxi, B[m - 1] + B[m - 2]);
  }

  int mini = (n && m) ? A[0] + B[0] + h : inf;
  if (n > 1) {
    mini = min(mini, A[0] + A[1]);
  }
  if (m > 1) {
    mini = min(mini, B[0] + B[1]);
  }

  return maxi - mini;
}

int main(void) {
  int n, h;
  scanf("%i %i", &n, &h);

  vector<int> S(n);
  for (int &s : S) {
    scanf("%i", &s);
  }

  map<int, vector<int>> mp;
  for (int i = 0; i < n; i++) {
    mp[S[i]].push_back(i);
  }

  sort(begin(S), end(S));

  deque<int> A(S.begin(), S.end());
  deque<int> B;

  int best = calc(A, B, h);
  int sep = 0;

  for (int i = 0; i < n; i++) {
    B.push_back(A.front());
    A.pop_front();
    int value = calc(A, B, h);
    if (value < best) {
      best = value;
      sep = i + 1;
    }
  }

  vector<int> answer(n, 2);
  for (int i = 0; i < sep; i++) {
    answer[mp[S[i]].back()] = 1;
    mp[S[i]].pop_back();
  }

  printf("%i\n", best);
  for (int i : answer) {
    printf("%i ", i);
  }
  puts("");

  return 0;
}

