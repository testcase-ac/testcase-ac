#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;
  ll sq1 = sqrt(n), sq2 = sqrt(n / 2);
  cout << n - sq1 - sq2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
