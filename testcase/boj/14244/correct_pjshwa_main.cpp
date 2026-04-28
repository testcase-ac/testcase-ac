#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n - m; i++) cout << i - 1 << ' ' << i << '\n';
  for (int i = n - m + 1; i <= n - 1; i++) cout << "0 " << i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
