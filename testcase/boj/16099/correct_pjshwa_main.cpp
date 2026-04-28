#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  if (a * b > c * d) cout << "TelecomParisTech\n";
  else if (a * b < c * d) cout << "Eurecom\n";
  else cout << "Tie\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
