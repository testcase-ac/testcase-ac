#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  
  int hz = 0;
  for (int i = 0; i < n; i++) {
    double p; cin >> p;
    hz += p == 0.5;
  }

  ll ans = (1LL << hz) - 1;
  ans *= (1LL << (n - hz));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
