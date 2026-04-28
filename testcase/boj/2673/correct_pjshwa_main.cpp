#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, dp[101][101];
bool adj[101][101];

int dfs(int s, int e) {
  if (s == e) return 0;
  if (dp[s][e] != -1) return dp[s][e];
  int ans = 0;
  for (int i = s; i < e; i++) ans = max(ans, dfs(s, i) + dfs(i + 1, e));
  return dp[s][e] = ans + adj[s][e];
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a][b] = adj[b][a] = 1;
  }
  memset(dp, -1, sizeof(dp));
  cout << dfs(1, 100);
}
