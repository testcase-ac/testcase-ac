#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int A = 0, B = 1;
  for (int i = 2; i <= N; i++) {
    int C = A + B;
    A = B; B = C;
  }
  cout << A << ' ' << B << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
