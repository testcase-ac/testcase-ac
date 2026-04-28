#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int acc = -8;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    acc += (x + 8);
  }

  cout << acc / 24 << ' ' << acc % 24 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
