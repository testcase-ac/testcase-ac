#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

const int MAX = 100;
const ll INF = 1e18;
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];
bool check[MAX + 1][MAX + 1];

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  if (n == 1 && m > 0) return cout << "0\n", void();

  vector<tii> ws;
  for (int i = 1; i <= n - 1; i++) {
    for (int j = i + 1, d; j <= n; j++) {
      cin >> d;
      ws.push_back({d, i, j});
    }
  }
  sort(ws.begin(), ws.end());

  for (auto &x : ws) {
    auto [wgt, u, v] = x;

    dijk(u);
    if (cdist[v] < wgt) return cout << "0\n", void();
    if (cdist[v] > wgt) {
      graph[u].push_back({v, wgt});
      graph[v].push_back({u, wgt});
    }
  }

  for (auto &x : ws) {
    auto [wgt, u, v] = x;

    dijk(u);
    assert(cdist[v] == wgt && wgt <= 500);
  }

  vector<tii> ans;
  for (int i = 1; i <= n; i++) {
    for (auto &el : graph[i]) {
      auto [v, wgt] = el;
      if (v < i) continue;
      check[i][v] = check[v][i] = true;
      ans.push_back({i, v, wgt});
    }
  }

  if (ans.size() > m) cout << "0\n";
  else {
    cout << "1\n";
    int rem = m - ans.size();
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        if (check[i][j]) continue;
        if (rem) ans.push_back({i, j, 500}), rem--;
      }
    }
    if (ans.size() < m) return cout << "0\n", void();
    for (auto& [u, v, wgt] : ans) cout << u << ' ' << v << ' ' << wgt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
