#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int a, b; cin >> a >> b;

  vector<vector<int>> cdist(b + 1, vector<int>(2, INF));
  queue<pii> Q;
  Q.emplace(a, 0); cdist[a][0] = 0;

  while (!Q.empty()) {
    auto [v, t] = Q.front(); Q.pop();
    for (auto& [nv, nt] : {make_pair(v + 1, t), make_pair(v * 2, t), make_pair(v * 10, t + 1)}) {
      if (nv < 0 || nv > b || nt > 1) continue;
      if (cdist[nv][nt] != INF) continue;
      cdist[nv][nt] = cdist[v][t] + 1;
      Q.emplace(nv, nt);
    }
  }

  cout << min(cdist[b][0], cdist[b][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
