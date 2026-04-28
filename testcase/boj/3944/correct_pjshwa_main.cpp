#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int b; string d;
  cin >> b >> d;

  int ans = 0;
  for (char& c : d) ans = (ans + (c - '0')) % (b - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
