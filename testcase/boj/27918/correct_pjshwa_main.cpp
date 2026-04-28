#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int d = 0, p = 0;
  for (int i = 0; i < N; i++) {
    string U; cin >> U;
    if (U == "D") d++;
    if (U == "P") p++;

    if (abs(d - p) >= 2) break;
  }
  cout << d << ':' << p << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
