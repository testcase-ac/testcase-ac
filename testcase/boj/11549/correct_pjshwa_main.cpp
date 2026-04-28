#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}
void solve() {
  int t, a[5];
  cin >> t >> a[0] >> a[1] >> a[2] >> a[3] >> a[4];

  int ans = 0;
  for (int i = 0; i < 5; i++) ans += a[i] == t;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
