#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, flag = 0; cin >> N;

  ll ans1 = 0, ans2 = 0;
  for (int b = 0; b < 16; ++b) {
    if (N & (1LL << b)) ans1 += 1LL << b;
  }
  for (int b = 16; b < 32; ++b) {
    if (N & (1LL << b)) ans2 += 1LL << (31 - b);
  }

  if (ans2 > 0) ++ans2;
  cout << ans1 + ans2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
