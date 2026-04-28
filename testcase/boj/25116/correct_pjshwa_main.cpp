#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e5;
ll a[MAX];
ll n, m, k;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool check(ll add) {
  ll cnt = 0, run = 0, ep = 0;
  for (int sp = 0; sp < n; sp++) {
    while (ep < n && run < m) {
      run += a[ep] + add;
      ep++;
    }
    if (run >= m) cnt += (n - ep + 1);
    run -= a[sp] + add;
  }
  return cnt >= k;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll left = 0, right = 2e18;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (check(mid)) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
