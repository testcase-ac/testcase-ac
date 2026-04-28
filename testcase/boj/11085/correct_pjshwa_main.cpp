#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<tuple<int, int, int>> graph[MAX + 1];
int cw;

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
      auto [vi, di, hi] = p;
      if (hi < cw) continue;

      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m, s, e;
  cin >> n >> m >> s >> e;
  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].push_back({b, 1, w});
  }

  int left = 1, right = 1001;
  while (left < right) {
    cw = (left + right) / 2;
    dijk(s);
    if (cdist[e] != INF) left = cw + 1;
    else right = cw;
  }

  cout << left + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
