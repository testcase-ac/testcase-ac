#include <bits/stdc++.h>
using namespace std;
 
bool vis[21];
int n, mx;

void dfs_mark(int cn, int c) {
  mx = max(c, mx);
  if (cn > n) return;

  dfs_mark(cn + 1, c);
  for (int i = 1; i < cn; i++) for (int j = i + 1; j < cn; j++) {
    if (vis[i] && vis[j] && (i ^ j) == cn) return;
  }
  vis[cn] = true;
  dfs_mark(cn + 1, c + 1);
  vis[cn] = false;
}

bool printed;
void dfs_print(int cn, int c) {
  if (printed) return;
  if (c == mx) {
    for (int i = 1; i <= n; i++) if (vis[i]) cout << i << ' ';
    printed = true;
    return;
  }
  if (cn > n) return;

  dfs_print(cn + 1, c);
  for (int i = 1; i < cn; i++) for (int j = i + 1; j < cn; j++) {
    if (vis[i] && vis[j] && (i ^ j) == cn) return;
  }
  vis[cn] = true;
  dfs_print(cn + 1, c + 1);
  vis[cn] = false;
}

void solve() {
  memset(vis, 0, sizeof(vis));
  cin >> n;
  mx = 0;
  dfs_mark(1, 0);

  cout << mx << '\n';
  printed = false;
  dfs_print(1, 0);
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) solve();

}
