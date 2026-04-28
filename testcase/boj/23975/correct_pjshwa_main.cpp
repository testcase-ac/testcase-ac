#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
const ll INF = 1e18;
int a[MAX + 1];
int from[MAX + 1], root[MAX + 1];
ll cdist[MAX + 1];
vector<pll> graph[MAX + 1];

int find_root(int n) {
  if (root[n] == n) return n;
  return root[n] = find_root(root[n]);
}

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
      if (cdist[vi] > di + wi || (cdist[vi] == di + wi && from[vi] < ui)) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) cin >> a[i], root[i] = i;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back({b, c});
    graph[b].push_back({a, c});
  }
  dijk(1);

  while (q--) {
    int x;
    cin >> x;

    if (cdist[x] == INF) {
      cout << "-1\n";
      continue;
    }

    x = find_root(x);
    while (!a[x]) {
      if (x == 1) {
        x = -1;
        break;
      }
      root[x] = find_root(from[x]);
      x = root[x];
    }
    cout << x << '\n';
    if (x != -1) a[x]--;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
