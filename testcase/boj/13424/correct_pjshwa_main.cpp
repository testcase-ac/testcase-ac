#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }

  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    cost[a][b] = cost[b][a] = w;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int k;
  cin >> k;
  vector<int> f(k);
  for (int i = 0; i < k; i++) cin >> f[i];

  int mi = -1, mv = INF;
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (int j = 0; j < k; j++) cur += cost[i][f[j]];
    if (cur < mv) {
      mv = cur;
      mi = i;
    }
  }

  cout << mi << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
