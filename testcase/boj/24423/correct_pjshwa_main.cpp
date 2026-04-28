#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int h, w, n;
  cin >> h >> w >> n;

  vector<pii> s;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    s.push_back({x, y});
  }
  sort(s.begin(), s.end());

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int cur;
    auto [x, y] = s[i];

    for (int xdt : {0, 2}) for (int ydt : {0, 1, 2}) {
      cur = 0;
      for (int xi = x - 2 + xdt; xi <= x + xdt; xi++) for (int yi = y - 2 + ydt; yi <= y + ydt; yi++) {
        cur += upper_bound(s.begin(), s.end(), pii(xi, yi)) - lower_bound(s.begin(), s.end(), pii(xi, yi));
      }
      ans = max(ans, cur);
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
