#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<pair<int, pii>> up, down;
  vector<int> xs;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    up.push_back({x1, {y1, y2}});
    down.push_back({x2, {y1, y2}});
    xs.push_back(x1);
    xs.push_back(x2);
  }
  sort(up.begin(), up.end());
  reverse(up.begin(), up.end());
  sort(down.begin(), down.end());
  reverse(down.begin(), down.end());

  compress(xs);

  ll ans = 0, lastx = xs[0];
  multiset<pii> cur;
  for (int x : xs) {
    ll dt = 0, lasty = 0;
    for (auto [y, d] : cur) {
      if (dt) ans += (x - lastx) * (y - lasty);
      dt += d;
      lasty = y;
    }

    while (!up.empty() && up.back().first == x) {
      auto [_, p] = up.back();
      up.pop_back();

      auto [y1, y2] = p;
      cur.insert({y1, 1});
      cur.insert({y2, -1});
    }

    while (!down.empty() && down.back().first == x) {
      auto [_, p] = down.back();
      down.pop_back();

      auto [y1, y2] = p;
      cur.erase(cur.find({y1, 1}));
      cur.erase(cur.find({y2, -1}));
    }

    lastx = x;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
