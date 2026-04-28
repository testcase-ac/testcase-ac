#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double A1, P1, R1, P2;
  cin >> A1 >> P1 >> R1 >> P2;

  double A2 = R1 * R1 * M_PI;
  double W1 = A1 / P1, W2 = A2 / P2;

  if (W1 > W2) cout << "Slice of pizza\n";
  else cout << "Whole pizza\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
