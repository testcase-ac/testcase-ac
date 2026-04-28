#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  reverse(a, a + n);

  int i = 0, ans = 0;
  while (1) {
    int tar = a[i] * m;
    int cur = 0;
    while (i < n && cur < tar) {
      cur += a[i];
      i++;
    }
    ans += tar / m;
    if (i == n) break;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
