#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, l, r;
  cin >> n >> l >> r;

  map<int, ll> L, R, LG, RG, G;
  for (int i = 0; i < n; i++) {
    int xi, di, wi;
    cin >> xi >> di >> wi;
    if (xi < 0) {
      if (di == 1) xi = -xi;
      else xi = 2 * l + 1 + xi;

      L[xi] += wi;
    }
    else {
      if (di == 1) xi = 2 * r + 1 - xi;

      R[xi] += wi;
    }
  }

  int g = __gcd(2 * l, 2 * r);
  int lim = 2 * r / g;
  map<int, priority_queue<int, vector<int>, greater<int>>> u;

  for (auto [k, v] : L) {
    int nk = k % g;
    if (u[nk].size() == lim) {
      if (u[nk].top() >= v) continue;
      u[nk].pop();
    }
    u[nk].push(v);
  }
  for (auto [k, v] : R) {
    int nk = k % g;
    if (u[nk].size() == lim) {
      if (u[nk].top() >= v) continue;
      u[nk].pop();
    }
    u[nk].push(v);
  }

  ll ans = 0;
  for (auto [k, q] : u) {
    while (!q.empty()) ans += q.top(), q.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
