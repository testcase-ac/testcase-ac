#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M; cin >> M;

  ll n = 180 * M * M - 2 * M * M * M;
  ll d = 60 * 60 * 60;

  ll g = gcd(n, d);
  cout << n / g << '/' << d / g << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
