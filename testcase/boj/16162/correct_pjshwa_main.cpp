#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, A, D; cin >> N >> A >> D;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x == A) ans++, A += D;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
