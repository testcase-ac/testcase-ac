#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int r(int n, int p) {
  if (n == 1) return 1;

  if (n & 1) {
    if (p) {
      return 2 * r(n / 2, 0);
    }
    else {
      return 2 * r((n + 1) / 2, 1) - 1;
    }
  }
  else {
    if (p) {
      return 2 * r(n / 2, 1);
    }
    else {
      return 2 * r(n / 2, 0) - 1;
    }
  }
}

void solve() {
  int N;
  cin >> N;
  cout << r(N, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
