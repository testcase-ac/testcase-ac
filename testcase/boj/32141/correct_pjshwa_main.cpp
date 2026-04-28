#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, H; cin >> N >> H;

  int sum = 0;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    sum += x;
    if (sum >= H) return cout << i << '\n', void();
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
