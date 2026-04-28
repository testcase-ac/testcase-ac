#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
vector<pll> graph[MAX + 1];
bool vis[MAX + 1];

const ll INF = 1e18;
ll cdist[MAX + 1];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &[vi, di] : graph[ui]) {
      if (cdist[vi] > cdist[ui] + di) {
        cdist[vi] = cdist[ui] + di;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int ai, bi, ci;
    cin >> ai >> bi >> ci;
    graph[ai].push_back({bi, ci});
    graph[bi].push_back({ai, ci});
  }

  dijk(0);

  ll ans = 0;
  queue<pll> q;
  q.push({n - 1, cdist[n - 1]});
  vis[n - 1] = 1;

  while (!q.empty()) {
    auto [u, ud] = q.front();
    q.pop();

    for (auto &[v, d] : graph[u]) {
      if (cdist[v] != ud - d) continue;
      ans += d;

      if (!vis[v]) q.push({v, ud - d}), vis[v] = 1;
    }
  }

  cout << 2 * ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
