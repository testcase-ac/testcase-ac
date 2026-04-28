#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string A, B;
  cin >> A >> B;

  int Az = A.size(), As = 0, Bz = B.size(), Bs = 0;
  for (char& c : A) As += c - '0';
  for (char& c : B) Bs += c - '0';

  int Au = Az * As, Bu = Bz * Bs;
  if (Au > Bu) cout << "1\n";
  else if (Au < Bu) cout << "2\n";
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
