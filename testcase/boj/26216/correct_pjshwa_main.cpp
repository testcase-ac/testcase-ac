#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int K, H, Q; cin >> K >> H >> Q;

  ll tot = 1;
  for (int i = 0; i < H; i++) tot *= (K + 1);
  tot--;

  while (Q--) {
    ll A, B; cin >> A >> B;
    if (A > tot || B > tot) {
      cout << "-1\n";
      continue;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
