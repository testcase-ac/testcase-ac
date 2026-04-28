#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  int a[n], r[n];
  bool w[n];
  for (int i = 0; i < n; i++) cin >> a[i], w[i] = false;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    w[x - 1] = true;
  }
  for (int i = 0; i < n; i++) {
    if (w[i]) r[i] = a[i];
    else {
      for (int j = 1; j <= 5; j++) {
        if (a[i] == j) continue;
        if (i > 0 && r[i - 1] == j) continue;
        if (i < n - 1 && w[i + 1] && a[i + 1] == j) continue;
        r[i] = j;
        break;
      }
    }
  }

  for (int i = 0; i < n; i++) cout << r[i] << " ";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
