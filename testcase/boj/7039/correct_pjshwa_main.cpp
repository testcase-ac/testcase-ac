#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 25000, MAXC = 1e6;
vector<tii> Xs[MAXC + 1], Ys[MAXC + 1];
int ban[MAXN];

void solve() {
  int N; cin >> N;
  map<pii, int> corners_cnt;
  vector<tuple<int, int, int, int, int>> points;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    ++corners_cnt[{x1, y1}]; ++corners_cnt[{x2, y2}];
    ++corners_cnt[{x1, y2}]; ++corners_cnt[{x2, y1}];

    Xs[x1].emplace_back(y1, y2, i); Xs[x2].emplace_back(y1, y2, i);
    Ys[y1].emplace_back(x1, x2, i); Ys[y2].emplace_back(x1, x2, i);

    points.emplace_back(x1, y1, x2, y2, i);
  }

  // corners check
  for (auto& [x1, y1, x2, y2, i] : points) {
    bool ok = false;
    ok |= corners_cnt[{x1, y1}] > 1;
    ok |= corners_cnt[{x2, y2}] > 1;
    ok |= corners_cnt[{x1, y2}] > 1;
    ok |= corners_cnt[{x2, y1}] > 1;
    if (ok) ban[i] = 1;
  }

  for (int x = 0; x <= MAXC; ++x) {
    sort(Xs[x].begin(), Xs[x].end());
    int lasty = -1, lasti = -1;
    for (auto& [y1, y2, i] : Xs[x]) {
      if (y1 <= lasty) ban[i] = ban[lasti] = 1;
      if (y2 >= lasty) lasty = y2, lasti = i;
    }
  }
  for (int y = 0; y <= MAXC; ++y) {
    sort(Ys[y].begin(), Ys[y].end());
    int lastx = -1, lasti = -1;
    for (auto& [x1, x2, i] : Ys[y]) {
      if (x1 <= lastx) ban[i] = ban[lasti] = 1;
      if (x2 >= lastx) lastx = x2, lasti = i;
    }
  }

  // cout << "ban = ";
  // for (int i = 0; i < N; ++i) cout << ban[i] << ' ';
  // cout << '\n';

  int ans = N;
  for (int i = 0; i < N; ++i) ans -= ban[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
