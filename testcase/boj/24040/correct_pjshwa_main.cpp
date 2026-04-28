#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n;
  cin >> n;

  if (n % 9 == 2 || n % 9 == 0 || n % 9 == 5 || n % 9 == 8) cout << "TAK\n";
  else cout << "NIE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
