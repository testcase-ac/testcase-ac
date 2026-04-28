#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX], b[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];

  int ans = 0;
  for (int i = 0; i < max(n, m); i++) ans = max(ans, b[i] - a[i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
