#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool adj[201][201];
int o[201], e[201][201];

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

int main() {
  fast_io();

  int n, m, u, v;
  cin >> n >> m;
  while (m--) {
    cin >> u >> v;
    adj[u][v] = adj[v][u] = true;
  }

  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) for (int k = j + 1; k <= n; k++) {
    if (!(adj[i][j] && adj[j][k] && adj[k][i])) continue;

    o[i]++; o[j]++; o[k]++;
    e[i][j]++; e[i][k]++; e[j][k]++;
    e[j][i]++; e[k][i]++; e[k][j]++;
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += nC2(o[i]);
    for (int j = 1; j <= n; j++) ans -= nC2(e[i][j]);
  }
  cout << ans;
}
