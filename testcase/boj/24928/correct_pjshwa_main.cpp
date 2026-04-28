#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; int D; cin >> S >> D;

  int p = 1;
  for (char c : S) {
    D += p * (c == 'B');
    p *= 2;
  }

  for (char c : S) {
    cout << (D & 1 ? 'B' : 'A');
    D /= 2;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
