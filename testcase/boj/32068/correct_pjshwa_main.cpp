#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, R, S; cin >> L >> R >> S;
  int ld = abs(L - S), rd = abs(R - S);
  if (rd <= ld) cout << 2 * rd << '\n';
  else cout << 2 * ld + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
