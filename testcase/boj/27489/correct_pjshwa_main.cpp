#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;

  if (n % 2 == 0) return cout << "nO\n", void();
  cout << "yEs\n";

  int M = 2 * n + 1, H = (n + 1) / 2;
  for (int i = 0; i < H; i++) {
    cout << n - 2 * i << ' ' << (M - i) - (n - 2 * i) << '\n';
  }
  for (int i = 1; i <= H - 1; i++) {
    cout << 2 * i << ' ' << (M + i) - (2 * i) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
