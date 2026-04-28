#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B;
  cin >> A >> B;
  if (A > B || B % A) return cout << "0\n", void();

  int U = B / A, ans = 0;
  for (int f = 1; f * f <= U; f++) {
    if (U % f) continue;
    int s = U / f;
    ans++;
    if (f != s) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
