#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int f(int a, int b, int c) {
  int ans = 0;
  for (int i = 0; i <= a; ++i) for (int j = 0; j <= b; ++j) {
    if (i + j == c) ++ans;
  }
  return ans;
}

void solve() {
  int n, m; cin >> n >> m;

  int ans = 0;
  for (int i = 0; i <= n + m; ++i) ans += f(n, m, i);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
