#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, P;
  cin >> A >> P;

  int Av = 7 * A, Pv = 13 * P;
  if (Av < Pv) cout << "Petra\n";
  else if (Av > Pv) cout << "Axel\n";
  else cout << "lika\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
