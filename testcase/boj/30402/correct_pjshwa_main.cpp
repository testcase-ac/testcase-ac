#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  for (int i = 0; i < 225; ++i) {
    string S; cin >> S;
    if (S == "w") return cout << "chunbae\n", void();
    if (S == "b") return cout << "nabi\n", void();
    if (S == "g") return cout << "yeongcheol\n", void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
