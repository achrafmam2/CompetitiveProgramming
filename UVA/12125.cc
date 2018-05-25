/// March of the Penguins
/// Build a network flow where the pieces of ice are nodes in the network. Each node
/// has a capacity which is equal to the capacity of the ice, and two nodes are connected
/// iff their distance is less than or equal to `D`.
/// The penguins can gather in some piece of ice `Sink` iff the maximum flow in the network
/// from all the other pieces of ice to the `Sink` is equal to the total number of penguins.
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>

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

int main(void) {
  int T;
  scanf("%i", &T);

  while (T--) {
    int n;
    double d;
    scanf("%i %lf", &n, &d);

    int tot = 0;
    vector<int> X(n), Y(n), cap(n), count(n);
    for (int i = 0; i < n; i++) {
      scanf("%i %i %i %i", &X[i], &Y[i], &count[i], &cap[i]);
      tot += count[i];
    }

    auto first = [](int a) { return 2 * a; };
    auto second = [](int a) { return 2 * a + 1; };

    vector<int> ans;
    for (int sink = 0; sink < n; sink++) {
      const int kSource = 2 * n;
      const int inf = 10000000;

      PushRelabel g = PushRelabel(2 * n + 1);

      for (int i = 0; i < n; i++) {
        g.AddEdge(kSource, first(i), count[i]);
        g.AddEdge(first(i), second(i), cap[i]);
      }

      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (hypot(X[i] - X[j], Y[i] - Y[j]) > d) {
            continue;
          }
          g.AddEdge(second(i), first(j), inf);
          g.AddEdge(second(j), first(i), inf);
        }
      }

      long long flow = g.GetMaxFlow(kSource, first(sink));
      if (flow == tot) {
        ans.push_back(sink);
      }
    }

    if (ans.empty()) {
      puts("-1");
    } else {
      for (int i = 0; i < ans.size(); i++) {
        printf("%i%c", ans[i], (i + 1 < ans.size()) ? ' ' : '\n');
      }
    }
  }

  return 0;
}
