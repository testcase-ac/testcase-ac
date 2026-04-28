#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int h[MAX], y[MAX];
int hl, yl, k;

bool check(ll v) {
  int sthan = 0;
  sthan += upper_bound(h, h + hl, v) - h;
  sthan += upper_bound(y, y + yl, v) - y;
  return sthan >= k;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) cin >> h[i];
  for (int i = 0; i < n; ++i) cin >> y[i];

  int q;
  cin >> q;
  while (q--) {
    cin >> hl >> yl >> k;

    ll left = 1, right = max(h[hl - 1], y[yl - 1]);
    while (left < right) {
      ll mid = (left + right) / 2;
      if (check(mid)) right = mid;
      else left = mid + 1;
    }

    auto it1 = lower_bound(h, h + hl, left);
    auto it2 = lower_bound(y, y + yl, left);
    if (*it1 == left) cout << "1 " << it1 - h + 1 << '\n';
    if (*it2 == left) cout << "2 " << it2 - y + 1 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
