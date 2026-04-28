#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool adj[301][301];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj[a][b] = adj[b][a] = true;
  }

  // Can we make a complete graph using 2 * n - 2 edges?
  // if n <= 4, then yes
  // if n >= 5, then no

  vector<pair<int, int>> ans;
  if (n <= 4) {
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
      if (!adj[i][j]) ans.push_back({i, j});
    }
    cout << ans.size() << '\n';
    cout << 1 << '\n';
    for (auto p : ans) cout << p.first << ' ' << p.second << '\n';
  }
  else {
    for (int j = 2; j <= n; j++) {
      if (!adj[1][j]) ans.push_back({1, j});
    }
    cout << ans.size() << '\n';
    cout << 2 << '\n';
    for (auto p : ans) cout << p.first << ' ' << p.second << '\n';
  }
}
