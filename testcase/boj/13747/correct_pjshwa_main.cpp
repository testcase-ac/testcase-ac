#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;
  map<ll, vector<ll>> ps;
  while (k--) {
    ll a, b;
    cin >> a >> b;
    ps[b].push_back(a);
  }

  map<ll, ll> d;
  d[0] = 0;
  ll lp = 0;
  for (auto [k, vv] : ps) {
    d[k] = d[lp];
    for (ll& v : vv) {
      auto it = d.lower_bound(v);
      it--;
      d[k] = max(d[k], it->second + k + 1 - v);
    }
    lp = k;
  }

  cout << n - d[lp] << '\n';
}
