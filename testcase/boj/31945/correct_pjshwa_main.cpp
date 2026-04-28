#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int P[4];
  for (int i = 0; i < 4; ++i) cin >> P[i];

  for (int b : {1, 2, 4}) {
    set<int> U;
    for (int i = 0; i < 4; ++i) U.insert(P[i] & b);
    if (U.size() == 1) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
