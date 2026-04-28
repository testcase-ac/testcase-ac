#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
vector<int> graph[MAX];
int a[MAX], b[MAX];
int ma[MAX], mb[MAX];
bool vis[MAX];
int n, m;
// int tc;

bool dfs(int v) {
  vis[v] = true;
  int w = a[v];

  for (int i = 0; i < m; i++) {
    int p = b[i];
    if (
      (w <= p * 2 && 4 * p <= w * 3) ||
      (w <= p && 4 * p <= w * 5)
    ) {
      if (mb[i] == -1 || !vis[mb[i]] && dfs(mb[i])) {
        ma[v] = i;
        mb[i] = v;
        return true;
      }
    }
  }
  return false;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < n; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) match++;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
