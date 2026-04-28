#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int deg[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  vector<pii> edges; queue<int> q;
  int it = 1; q.push(it++);
  while (!q.empty() && it <= N) {
    int u = q.front(); q.pop();
    while (deg[u] < K && it <= N) {
      int v = it++;
      edges.emplace_back(u, v);
      deg[u]++; deg[v]++;
      q.push(v);
    }
  }

  for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
