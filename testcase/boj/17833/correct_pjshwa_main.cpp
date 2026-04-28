#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
const ll INF = 1e14;
tii buildings[MAX];
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

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

void solve() {
  int n, r, d, m;
  cin >> n >> r >> d >> m;

  for (int i = 0; i < m; i++) {
    int hi, ti, ei1, ei2;
    cin >> hi >> ti >> ei1 >> ei2;
    buildings[i] = make_tuple(hi, ti, ei1, ei2);
  }

  for (int i = 1; i <= n; i++) for (int j = 0; j < m; j++) {
    int hi, ti, ei1, ei2;
    tie(hi, ti, ei1, ei2) = buildings[j];
    if (i >= ei1 && i + hi - ei1 <= n) {
      int nxt = i + (ei2 - ei1);
      if (1 <= nxt && nxt <= n) graph[i].push_back({nxt, ti});
    }
    if (i >= ei2 && i + hi - ei2 <= n) {
      int nxt = i + (ei1 - ei2);
      if (1 <= nxt && nxt <= n) graph[i].push_back({nxt, ti});
    }
  }

  dijk(r);

  if (cdist[d] == INF) cout << "-1\n";
  else cout << cdist[d] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
