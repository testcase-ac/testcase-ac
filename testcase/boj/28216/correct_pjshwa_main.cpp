#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<pair<int, ll>> xs[MAXN + 1], ys[MAXN + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 0; i < N; ++i) {
    int xi, yi, wi; cin >> xi >> yi >> wi;
    xs[yi].emplace_back(xi, wi);
    ys[xi].emplace_back(yi, wi);
  }
  for (int i = 1; i <= MAXN; ++i) {
    if (!xs[i].empty()) {
      sort(xs[i].begin(), xs[i].end());
      for (int j = 1; j < (int)xs[i].size(); ++j) xs[i][j].second += xs[i][j - 1].second;
    }
    if (!ys[i].empty()) {
      sort(ys[i].begin(), ys[i].end());
      for (int j = 1; j < (int)ys[i].size(); ++j) ys[i][j].second += ys[i][j - 1].second;
    }
  }

  ll cx = 1, cy = 1, ans = 0;
  while (Q--) {
    ll dj, vj, sv, ev; cin >> dj >> vj;
    ll nx = cx + dx[dj] * vj, ny = cy + dy[dj] * vj;

    if (cx == nx) {
      int sy = cy < ny ? cy + 1 : ny;
      int ey = cy < ny ? ny : cy - 1;
      auto sb = lower_bound(ys[cx].begin(), ys[cx].end(), make_pair(sy, 0LL));
      auto eb = upper_bound(ys[cx].begin(), ys[cx].end(), make_pair(ey + 1, 0LL));
      sv = sb == ys[cx].begin() ? 0 : (--sb)->second;
      ev = eb == ys[cx].begin() ? 0 : (--eb)->second;
    } else {
      int sx = cx < nx ? cx + 1 : nx;
      int ex = cx < nx ? nx : cx - 1;
      auto sb = lower_bound(xs[cy].begin(), xs[cy].end(), make_pair(sx, 0LL));
      auto eb = upper_bound(xs[cy].begin(), xs[cy].end(), make_pair(ex + 1, 0LL));
      sv = sb == xs[cy].begin() ? 0 : (--sb)->second;
      ev = eb == xs[cy].begin() ? 0 : (--eb)->second;
    }

    assert(sv <= ev);
    ans += ev - sv;
    cx = nx, cy = ny;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
