#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1600;
int B[MAXN][MAXN], vis[MAXN], cnt;
vector<int> adj[MAXN];

void dfs(int i) {
  vis[i] = 1; ++cnt;
  for (int j : adj[i]) if (!vis[j]) dfs(j);
}

void solve() {
  int n; cin >> n;
  n *= n;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> B[i][j];

  // Uniqueness is always determined by the second to last row.
  int l1 = n - 1, l2 = n - 2;
  for (int j1 = 0; j1 < n; ++j1) for (int j2 = j1 + 1; j2 < n; ++j2) {
    int ok = B[l1][j1] == B[l2][j2] || B[l1][j2] == B[l2][j1];
    if (ok) adj[j1].push_back(j2), adj[j2].push_back(j1);
  }

  int j;
  for (j = 0; j < n; ++j) {
    if (!vis[j]) dfs(j);
    if (cnt == n) break;
  }
  cout << n * (n - 2) + j + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
