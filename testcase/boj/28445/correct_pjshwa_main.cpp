#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  set<string> A;
  for (int i = 0; i < 4; i++) {
    string x; cin >> x;
    A.insert(x);
  }
  for (auto x : A) for (auto y : A) {
    cout << x << ' ' << y << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
