/// Collector’s Problem
/// Build a trading network where the maximum flow is the maximum cards Bob can get.
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
#include <cassert>

using namespace std;

typedef long long LL;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
  from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel {
  int N;
  vector<vector<Edge>> G;
  vector<LL> excess;
  vector<int> dist, active, count;
  queue<int> Q;

  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(int from, int to, int cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (int i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
        dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
        Gap(dist[v]);
      else
        Relabel(v);
    }
  }

  LL GetMaxFlow(int s, int t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    LL totflow = 0;
    for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

struct CardTrading {
  const int kSource = 0;
  const int kSink = 1;
  const int inf = 1000000;


  int n, m;
  vector<vector<int>> count;
  int g[10][26][2];
  int f[10][26][2];

  CardTrading() {
    scanf("%i %i", &n, &m);
    count.resize(n, vector<int>(m + 1));
    for (int i = 0; i < n; i++) {
      int k;
      scanf("%i", &k);
      while (k--) {
        int card;
        scanf("%i", &card);
        count[i][card]++;
      }
    }
  }

  int id = 0;
  int next() {
    assert(id < 4 * m * n + 2);
    return id++;
  }

  int guard(int p, int c, int idx) {
    if (g[p][c][idx] == -1) {
      g[p][c][0] = next();
      g[p][c][1] = next();
    }
    return g[p][c][idx];
  }

  int card(int p, int c, int idx) {
    if (f[p][c][idx] == -1) {
      f[p][c][0] = next();
      f[p][c][1] = next();
    }
    return f[p][c][idx];
  }

  void init() {
    memset(g, -1, sizeof(g));
    memset(f, -1, sizeof(f));
  }

  int maxCards() {
    int have = 0;
    for (int i = 1; i <= m; i++) {
      if (count[0][i] >= 1) {
        have++;
      }
    }
    have += (int)build().GetMaxFlow(kSource, kSink);
    return have;
  }

  PushRelabel build() {
    init();
    PushRelabel net = PushRelabel(4 * m * n + 2);

    int source = next();
    int sink = next();

    for (int i = 0; i < n; i++) {
      for (int j = 1; j <= m; j++) {
        if (count[i][j] == 0) {
          net.AddEdge(guard(i, j, 0), guard(i, j, 1), 1);
        }
      }

      for (int j = 1; j <= m; j++) {
        if (count[i][j] > 1) {
          net.AddEdge(card(i, j, 0), card(i, j, 1), count[i][j] - 1);
        }
      }

      for (int j = 1; j <= m; j++) {
        for (int k = 1; k <= m; k++) {
          net.AddEdge(guard(i, j, 1), card(i, k, 0), inf);
        }
      }

      for (int j = 1; j <= m; j++) {
        for (int k = 0; k < n; k++) {
          if (k == i) continue;
          net.AddEdge(card(i, j, 1), guard(k, j, 0), inf);
        }
      }
    }

    for (int i = 1; i <= m; i++) {
      net.AddEdge(source, card(0, i, 0), inf);
    }

    for (int i = 1; i <= m; i++) {
      net.AddEdge(guard(0, i, 1), sink, inf);
    }

    return net;
  }
};

int main(void) {
  int T;
  scanf("%i", &T);

  for (int t = 1; t <= T; t++) {
    printf("Case #%i: %i\n", t, CardTrading().maxCards());
  }

  return 0;
}
