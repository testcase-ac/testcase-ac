#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
ll cdist[MAX + 1][MAX + 1];
vector<tll> graph[MAX + 1];
int N;

void dijk(int s) {
  for (int i = 0; i <= MAX; i++) {
    fill(cdist[i], cdist[i] + MAX + 1, INF);
  }
  cdist[0][s] = 0;

  priority_queue<tll, vector<tll>, greater<tll>> pq;
  pq.push({0, 0, s});

  while (!pq.empty()) {
    auto [wi, li, ui] = pq.top();
    pq.pop();

    if (wi > cdist[li][ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di, oi] = p;
      if (oi) {
        if (li < MAX && cdist[li + 1][vi] > di + wi) {
          cdist[li + 1][vi] = di + wi;
          pq.push({cdist[li + 1][vi], li + 1, vi});
        }
      }
      else {
        if (cdist[li][vi] > di + wi) {
          cdist[li][vi] = di + wi;
          pq.push({cdist[li][vi], li, vi});
        }
      }
    }
  }
}

void solve() {
  int N, M, L;
  cin >> N >> M >> L;
  while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w, 0});
    graph[v].push_back({u, w, 1});
  }

  dijk(1);
  for (int f = 0; f <= MAX; f++) {
    if (cdist[f][N] <= L) return cout << f << '\n', void();
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
