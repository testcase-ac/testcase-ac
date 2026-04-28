#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll sum_r(ll l, ll r) {
  ll rsum = r * (r + 1) / 2;
  ll lsum = l * (l - 1) / 2;
  return rsum - lsum;
}

void solve() {
  int N, M; cin >> N >> M;

  map<int, int> by_l;
  while (M--) {
    int h, l; cin >> h >> l;
    by_l[l] = max(by_l[l], N - h + 1);
  }

  int last_l = -1, last_h = -1; ll ans = 0;
  for (auto& [l, h] : by_l) {
    if (last_l != -1) {
      int len = l - last_l;
      int lh = max(1, last_h - len + 1), rh = last_h;
      if (h < lh) continue;

      ans += sum_r(lh, rh);
    }
    last_l = l; last_h = h;
  }
  ans += sum_r(1, last_h);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
