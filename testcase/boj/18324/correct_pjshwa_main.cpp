#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

// Max length Bessie can run with time t
ll rl(ll t, ll e) {
  if (t < e) return t * (t + 1) / 2;

  ll mx = (t + e) / 2;
  ll rlen = mx * mx - e * (e - 1) / 2;
  if ((t + e) & 1) rlen += mx;
  return rlen;
}

void solve() {
  int n, m, x;
  cin >> n >> m;
  while (m--) {
    cin >> x;

    int left = 1, right = 1e5;
    while (left < right) {
      int mid = (left + right) / 2;
      if (rl(mid, x) >= n) right = mid;
      else left = mid + 1;
    }
    cout << left << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
