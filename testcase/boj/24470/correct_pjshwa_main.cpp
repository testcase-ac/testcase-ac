#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 70, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1];
int kcost[MAX + 1][MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    if (i != j) cost[i][j] = cost[j][i] = INF;
  }
  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    cost[a][b] = min(cost[a][b], w);
  }

  for (int a = 1; a <= n; a++) {
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
      kcost[a][i][j] = kcost[a][j][i] = INF;
    }

    queue<pii> oq;
    oq.push({0, a});
    kcost[a][0][a] = 0;

    while (!oq.empty()) {
      auto [ki, vi] = oq.front();
      oq.pop();

      for (int j = 1; j <= n; j++) {
        int acost = cost[vi][j];
        if (ki < n && kcost[a][ki + 1][j] > kcost[a][ki][vi] + acost) {
          kcost[a][ki + 1][j] = kcost[a][ki][vi] + acost;
          oq.push({ki + 1, j});
        }
      }
    }

  }
  
  int k, q;
  cin >> k >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;

    int ans = kcost[a][min(k, n)][b];
    if (ans == INF) cout << "-1\n";
    else cout << ans << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
