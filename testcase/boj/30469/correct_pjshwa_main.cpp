#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, N; cin >> A >> B >> N;
  int T = B / 10;
  if (T != 1 && T != 3 && T != 7 && T != 9) return cout << "-1\n", void();

  int L = A % 10; cout << A;
  for (int i = 0; i < N - 4; ++i) {
    if (L == 9) cout << 7, L = 7;
    else cout << 1, L = 1;
  }
  cout << B << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
