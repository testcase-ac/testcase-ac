#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
vector<int> graph[MAX + 1];
bool vis[MAX + 1];

vector<int> ans;
void dfs(int v) {
  vis[v] = 1;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
  ans.push_back(v);
}

void solve() {
  int n;
  cin >> n;
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
  // cin >> t;
  while (t--) solve();
}
