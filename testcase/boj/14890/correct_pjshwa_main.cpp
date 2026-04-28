#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int b[MAX][MAX], a[MAX], n, l;

bool passable() {
  bool vis[n];
  memset(vis, 0, sizeof(vis));

  for (int i = 0; i < n - 1; i++) {
    if (abs(a[i] - a[i + 1]) >= 2) return false;
    if (a[i] == a[i + 1] - 1) {
      for (int j = i; j > i - l; j--) {
        if (j < 0 || vis[j]) return false;
        vis[j] = true;
      }
    }
    if (a[i] == a[i + 1] + 1) {
      for (int j = i + 1; j <= i + l; j++) {
        if (j >= n || vis[j]) return false;
        vis[j] = true;
      }
    }
  }
  return true;
}

void solve() {
  cin >> n >> l;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> b[i][j];

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) a[j] = b[i][j];
    if (passable()) ans++;
  }
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) a[i] = b[i][j];
    if (passable()) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
