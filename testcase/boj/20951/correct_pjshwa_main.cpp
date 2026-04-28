#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1];
int d[10][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  for (int i = 1; i <= N; i++) d[0][i] = 1;
  for (int t = 1; t <= 7; t++) {
    for (int i = 1; i <= N; i++) {
      for (int j : graph[i]) d[t][i] = (d[t][i] + d[t - 1][j]) % MOD;
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) ans = (ans + d[7][i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
