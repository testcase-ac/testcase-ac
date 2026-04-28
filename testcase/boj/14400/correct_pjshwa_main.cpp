#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;

  sort(a, a + n, [] (pii a, pii b) {
    return a.first < b.first;
  });

  ll cur = 0;
  for (int i = 0; i < n; i++) cur += abs(a[i].first + (1e6 + 1));
  ll ans1 = cur;

  int si = 0, u = n, oi;
  for (int i = -1e6; i <= 1e6; i++) {
    cur -= (2 * u - n);
    while (si < n && a[si].first == i) u--, si++;
    ans1 = min(ans1, cur);
  }

  sort(a, a + n, [] (pii a, pii b) {
    return a.second < b.second;
  });

  cur = 0;
  for (int i = 0; i < n; i++) cur += abs(a[i].second + (1e6 + 1));
  ll ans2 = cur;

  si = 0, u = n;
  for (int i = -1e6; i <= 1e6; i++) {
    cur -= (2 * u - n);
    while (si < n && a[si].second == i) u--, si++;
    ans2 = min(ans2, cur);
  }

  cout << ans1 + ans2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
