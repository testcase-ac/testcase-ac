#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, b;
  cin >> a >> b;

  set<ll> traj{a};
  while (a > 1) {
    bool f = false;
    for (ll i = 2; i * i <= a; i++) {
      if (a % i) continue;

      a /= i;
      f = true;
      break;
    }
    if (!f) a = 1;
    traj.insert(a);
  }

  while (b > 1) {
    if (traj.count(b)) return cout << b << '\n', []{}();

    bool f = false;
    for (ll i = 2; i * i <= b; i++) {
      if (b % i) continue;

      b /= i;
      f = true;
      break;
    }
    if (!f) b = 1;
  }
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
