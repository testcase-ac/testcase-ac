#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, P;
  cin >> N >> P;

  int ans = P;
  if (N >= 5) ans = min(ans, max(0, P - 500));
  if (N >= 10) ans = min(ans, P * 9 / 10);
  if (N >= 15) ans = min(ans, max(0, P - 2000));
  if (N >= 20) ans = min(ans, P * 75 / 100);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
