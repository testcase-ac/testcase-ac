#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;
  if (n & (n + 1)) {
    int msb = 0;
    while (n >> msb) msb++;

    ll full = (1LL << msb) - 1;
    cout << "2\n" << (n ^ full) << '\n' << n << '\n';
  }
  else cout << "1\n" << n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
