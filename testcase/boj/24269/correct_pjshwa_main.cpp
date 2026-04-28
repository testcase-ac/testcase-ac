#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a[3], o[3];
int dist(pii& a, pii& b) {
  return abs(a.first - b.first) + abs(a.second - b.second);
}

void solve() {
  for (int i = 0; i < 3; i++) cin >> a[i], o[i] = a[i];
  sort(a, a + 3);

  ll ts = a[0] + a[1];
  if (ts < a[2]) return cout << "-1\n", void();
  if (ts % 2 != a[2] % 2) return cout << "-1\n", void();

  ll x1 = 0, y1 = 0, x2, y2, x3 = x1 + a[2], y3 = y1;
  ll mdiff = min(x3, 799'000'000LL);
  x3 -= mdiff, y3 += mdiff;

  ll cx = x1, cy = y1 + a[0];
  ll diff = (abs(x3 - cx) + abs(y3 - cy) - a[1]) / 2;
  if (diff > 0) {
    ll left = 1, right = 1e12;
    while (left < right) {
      ll mid = (left + right) / 2;
      if (abs(x3 - (cx + mid)) + abs(y3 - (cy - mid)) > a[1]) left = mid + 1;
      else right = mid;
    }
    x2 = cx + (left - 1), y2 = cy - (left - 1);
  }
  else {
    ll left = 1, right = 1e12;
    while (left < right) {
      ll mid = (left + right) / 2;
      if (abs(x3 - (cx - mid)) + abs(y3 - (cy - mid)) <= a[1]) left = mid + 1;
      else right = mid;
    }
    x2 = cx - (left - 1), y2 = cy - (left - 1);
  }
  // cout << "diff: " << diff << '\n';

  ll mx = -min({x1, x2, x3});
  ll my = -min({y1, y2, y3});
  x1 += (mx + 1), x2 += (mx + 1), x3 += (mx + 1);
  y1 += (my + 1), y2 += (my + 1), y3 += (my + 1);

  ll b[3] = {abs(x2 - x1) + abs(y2 - y1), abs(x3 - x2) + abs(y3 - y2),
             abs(x3 - x1) + abs(y3 - y1)};
  sort(b, b + 3);
  // for (int i = 0; i < 3; i++) cout << b[i] << ' ';
  // cout << endl;

  assert(a[0] == b[0]);
  assert(a[1] == b[1]);
  assert(a[2] == b[2]);
  assert(1 <= x1 && x1 <= 8e8);
  assert(1 <= y1 && y1 <= 8e8);
  assert(1 <= x2 && x2 <= 8e8);
  assert(1 <= y2 && y2 <= 8e8);
  assert(1 <= x3 && x3 <= 8e8);
  assert(1 <= y3 && y3 <= 8e8);

  pii ans[3];
  ans[0] = {x1, y1}, ans[1] = {x2, y2}, ans[2] = {x3, y3};
  int p[3] = {0, 1, 2};

  do {
    if (dist(ans[p[0]], ans[p[1]]) != o[0]) continue;
    if (dist(ans[p[1]], ans[p[2]]) != o[1]) continue;
    if (dist(ans[p[2]], ans[p[0]]) != o[2]) continue;

    cout << ans[p[0]].first << ' ' << ans[p[0]].second << ' ';
    cout << ans[p[1]].first << ' ' << ans[p[1]].second << ' ';
    cout << ans[p[2]].first << ' ' << ans[p[2]].second << '\n';
    break;
  } while (next_permutation(p, p + 3));
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
