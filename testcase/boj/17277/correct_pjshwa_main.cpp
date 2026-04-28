#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int v[MAX + 1];

void solve() {
  int n, x, y, z;
  cin >> n >> x >> y >> z;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (board[i][j] == '1') graph[i].push_back(j);
  }

  dfs(0);
  if (ans.size() == n) {
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << '\n';
  }
  else cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
