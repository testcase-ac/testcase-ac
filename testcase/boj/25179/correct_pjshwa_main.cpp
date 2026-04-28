#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, m;
  cin >> n >> m;

  if ((n - 1) % (m + 1)) cout << "Can win\n";
  else cout << "Can't win\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
