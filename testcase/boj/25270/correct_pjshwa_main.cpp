#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N;
  cin >> N;

  int diff = abs(N - 99), ans = 99;
  for (int i = 199; i <= 2e4; i += 100) {
    if (abs(N - i) <= diff) diff = abs(N - i), ans = i;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
