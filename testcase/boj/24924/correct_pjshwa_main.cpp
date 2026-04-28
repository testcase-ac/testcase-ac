#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll a, b;
  cin >> a >> b;

  ll d = (b - a + 1) % 9, rem = 0;
  for (ll i = b - d + 1; i <= b; i++) rem += (i % 9);
  cout << rem % 9 << '\n';
} 

int main() {
  fast_io();
  
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
