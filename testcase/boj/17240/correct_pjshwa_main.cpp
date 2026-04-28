#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4;
int a[MAX + 1][5], d[MAX + 1][1 << 5];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 0; j < 5; j++) cin >> a[i][j];

  for (int i = 1; i <= n; i++) for (int s = 0; s < (1 << 5); s++) {
    d[i][s] = d[i - 1][s];
    for (int j = 0; j < 5; j++) {
      if (s & (1 << j)) {
        d[i][s] = max(d[i][s], d[i - 1][s ^ (1 << j)] + a[i][j]);
      }
    }
  }

  cout << d[n][(1 << 5) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
