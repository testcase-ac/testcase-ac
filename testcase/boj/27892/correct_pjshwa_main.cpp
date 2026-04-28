#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll x0, N; cin >> x0 >> N;

  ll x = x0;
  map<ll, ll> d;
  for (int i = 1; i <= N; i++) {
    if (x % 2 == 0) x = (x / 2) ^ 6;
    else x = (2 * x) ^ 6;

    if (d.count(x)) {
      ll dif = i - d[x];
      ll rem = (N - i) % dif;
      for (int j = 0; j < rem; j++) {
        if (x % 2 == 0) x = (x / 2) ^ 6;
        else x = (2 * x) ^ 6;
      }
      break;
    }
    else d[x] = i;
  }
  cout << x << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
