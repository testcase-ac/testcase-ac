#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll K;
  cin >> K;
  K--;

  ll ans = 1;
  for (int i = 59; i >= 0; i--) {
    if (K & (1LL << i)) ans *= 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
