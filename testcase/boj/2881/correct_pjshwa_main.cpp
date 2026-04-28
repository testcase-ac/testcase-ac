#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;

  map<int, vector<int>> xs, ys;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    xs[x].push_back(y);
    ys[y].push_back(x);
  }
  for (auto& [k, v] : xs) sort(v.begin(), v.end());
  for (auto& [k, v] : ys) sort(v.begin(), v.end());

  int Q;
  cin >> Q;
  while (Q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    int ans = 0;
    ans += upper_bound(xs[x1].begin(), xs[x1].end(), y2) -
           lower_bound(xs[x1].begin(), xs[x1].end(), y1);
    ans += upper_bound(xs[x2].begin(), xs[x2].end(), y2) -
           lower_bound(xs[x2].begin(), xs[x2].end(), y1);
    if (x1 + 1 <= x2 - 1) {
      ans += upper_bound(ys[y2].begin(), ys[y2].end(), x2 - 1) -
             lower_bound(ys[y2].begin(), ys[y2].end(), x1 + 1);
      ans += upper_bound(ys[y1].begin(), ys[y1].end(), x2 - 1) -
             lower_bound(ys[y1].begin(), ys[y1].end(), x1 + 1);
    }

    cout << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
