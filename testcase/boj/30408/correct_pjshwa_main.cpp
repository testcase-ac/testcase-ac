#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, L; cin >> N >> L;
  ll U = L;

  while (N >= L) {
    if (L <= N && N <= U) return cout << "YES\n", void();
    L = 2 * L - 1;
    U = 2 * U + 1;
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
