#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  int E = 0, O = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x % 2 == 0) E++;
    else O++;
  }

  while (E < O) E++, O -= 2;

  int ans = 2 * O;
  if (E > O) ans++;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
