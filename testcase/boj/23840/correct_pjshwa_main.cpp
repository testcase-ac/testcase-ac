#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
ll w[22][22], d[1 << 20][20];
int p;

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

ll TSP(int state, int now) {
  if (state == (1 << p) - 1) return w[now][p + 1];

  ll& ret = d[state][now];
  if (ret != -1) return ret;

  ret = INF;
  for (int i = 0; i < p; i++) {
    if (~state & 1 << i) {
      auto res = TSP(state | 1 << i, i);
      if (res != INF) ret = min(ret, res + w[now][i]);
    }
  }
  return ret;
}

void solve() {
  int v, e;
  cin >> v >> e;

  while (e--) {
    int ui, vi, wi;
    cin >> ui >> vi >> wi;
    graph[ui].push_back({vi, wi});
    graph[vi].push_back({ui, wi});
  }

  int x, z;
  cin >> x >> z >> p;

  vector<int> points(p);
  for (int i = 0; i < p; i++) cin >> points[i];

  dijk(x);
  for (int i = 0; i < p; i++) w[p][i] = cdist[points[i]];
  dijk(z);
  for (int i = 0; i < p; i++) w[i][p + 1] = cdist[points[i]];

  for (int pi = 0; pi < p; pi++) {
    dijk(points[pi]);
    for (int j = 0; j < p; j++) w[pi][j] = cdist[points[j]];
  }

  ll ans = INF;
  memset(d, -1, sizeof d);
  for (int i = 0; i < p; i++) ans = min(ans, TSP(1 << i, i) + w[p][i]);
  
  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
