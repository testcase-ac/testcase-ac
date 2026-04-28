#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll upto(ll n) {
  ll ret = 0;
  for (int i = 1; i <= n; i++) {
    if (i & 1) ret -= (n / i);
    else ret += (n / i);
  }
  return ret;
}

void solve() {
  int S, T;
  cin >> S >> T;
  cout << upto(T) - upto(S - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
