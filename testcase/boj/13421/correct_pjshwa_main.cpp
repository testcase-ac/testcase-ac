#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

pii A[4];
ll f(ll k) {
  int p[4] = {0, 1, 2, 3};
  pair<ll, ll> B[4] = {
    {k, k},
    {-k, k},
    {-k, -k},
    {k, -k}
  };

  ll ans = 1e18;
  do {
    ll cur = 0;
    for (int i = 0; i < 4; i++) {
      auto [x1, y1] = A[i];
      auto [x2, y2] = B[p[i]];
      cur += abs(x1 - x2) + abs(y1 - y2);
    }
    ans = min(ans, cur);
  } while (next_permutation(p, p + 4));

  return ans;
}

void solve() {
  for (int i = 0; i < 4; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {2 * x, 2 * y};
  }

  ll left = 1, right = 1e10;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;
    if (f(mid1) < f(mid2)) right = mid2;
    else left = mid1;
  }

  ll mval = 1e18, ans;
  for (int i = right; i >= left; i--) {
    ll cur = f(i);
    if (cur < mval) {
      mval = cur;
      ans = i;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
