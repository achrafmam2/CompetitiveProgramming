/// Councilling
/// Build a network where the the maximum flow is equal to the number of assigned numbers.
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <set>

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

struct Elections {
  map<string, set<string>> club_members;
  map<string, string> which_party;

  Elections(map<string, set<string>> club_members, map<string, string> which_party) {
    this->club_members = club_members;
    this->which_party = which_party;
  }

  int id = 0;
  int next() { return id++; }

  map<string, string> elect() {
    set<string> parties;
    for (auto &node : which_party) {
      parties.insert(node.second);
    }

    map<string, int> party_idx, resident_idx, club_idx;

    for (auto &node : club_members) {
      club_idx[node.first] = next();
    }

    for (auto &node : which_party) {
      resident_idx[node.first] = next();
    }

    for (auto party : parties) {
      party_idx[party] = next();
    }

    int num_residents = (int)which_party.size();
    int num_clubs = (int)club_members.size();
    int num_parties = (int)parties.size();

    int source = next();
    int sink = next();

    PushRelabel net = PushRelabel(num_residents + num_clubs + num_parties + 2);

    for (auto &node : club_members) {
      string club = node.first;
      net.AddEdge(source, club_idx[club], 1);
      for (string r : node.second) {
        net.AddEdge(club_idx[club], resident_idx[r], 1);
      }
    }

    for (auto &node : which_party) {
      string r = node.first;
      string p = node.second;
      net.AddEdge(resident_idx[r], party_idx[p], 1);
    }

    int threshold = (num_clubs + 1) / 2 - 1;
    for (string p : parties) {
      net.AddEdge(party_idx[p], sink, threshold);
    }

    int flow = (int)net.GetMaxFlow(source, sink);
    if (flow < num_clubs) {
      return {};
    }

    map<int, string> resident_name;
    for (auto &node : resident_idx) {
      resident_name[node.second] = node.first;
    }

    map<string, string> presidents;
    for (auto &node : club_members) {
      string club = node.first;
      int cur_idx = club_idx[club];
      for (auto e : net.G[cur_idx]) {
        if (e.flow > 0) {
          presidents[resident_name[e.to]] = club;
          break;
        }
      }
    }

    return presidents;
  }
};

int main(void) {
  int T;
  cin >> T;

  string line;
  getline(cin, line);
  getline(cin, line);

  while (T--) {
    map<string, set<string>> club_members;
    map<string, string> which_party;
    while (getline(cin, line) && line != "") {
      istringstream ss(line);
      string name, party, club;
      ss >> name >> party;
      which_party[name] = party;
      while (ss >> club) {
        club_members[club].insert(name);
      }
    }

    auto presidents = Elections(club_members, which_party).elect();
    if (presidents.empty()) {
      cout << "Impossible." << endl;
    } else {
      for (auto node : presidents) {
        cout << node.first << " " << node.second << endl;
      }
    }

    if (T > 0) cout << endl;
  }

  return 0;
}
