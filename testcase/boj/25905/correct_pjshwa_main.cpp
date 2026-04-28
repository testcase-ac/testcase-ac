#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  vector<double> A(10);
  for (int i = 0; i < 10; ++i) cin >> A[i];
  sort(A.begin(), A.end());
  reverse(A.begin(), A.end());

  double nom = 1;
  for (int i = 0; i < 9; i++) nom = nom * (A[i] * 10);

  cout << fixed << setprecision(10) << nom / 362880 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
