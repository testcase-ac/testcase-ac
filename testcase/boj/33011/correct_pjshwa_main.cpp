#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, x, odd = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> x;
    if (x & 1) ++odd;
  }
  int even = N - odd;

  if (odd == even || max(odd, even) % 2 == 0) cout << "heeda0528\n";
  else cout << "amsminn\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
