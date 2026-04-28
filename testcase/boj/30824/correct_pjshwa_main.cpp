#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<ll> F;

void solve() {
  ll n, x; cin >> n >> x;
  if (n == 1) {
    for (ll e : F) {
      if (e == x) return void(cout << "YES\n");
    }
  }
  if (n == 2) {
    for (ll e1 : F) for (ll e2 : F) {
      if (e1 + e2 == x) return void(cout << "YES\n");
    }
  }
  if (n == 3) {
    for (ll e1 : F) for (ll e2 : F) for (ll e3 : F) {
      if (e1 + e2 + e3 == x) return void(cout << "YES\n");
    }
  }
  return void(cout << "NO\n");
}

int main() {
  fast_io();

  F.push_back(1); F.push_back(1);
  for (int i = 2; i <= 80; ++i) F.push_back(F[i - 1] + F[i - 2]);

  int t = 1;
  cin >> t;
  while (t--) solve();
}
