#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int B[MAXN + 1][MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;

  vector<int> xs, ys;
  vector<tuple<int, int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    A.emplace_back(x1, y1, x2, y2);
    xs.push_back(x1); xs.push_back(x2);
    ys.push_back(y1); ys.push_back(y2);
  }

  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  for (int i = 0; i < N; ++i) {
    auto [x1, y1, x2, y2] = A[i];
    x1 = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
    y1 = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
    x2 = lower_bound(xs.begin(), xs.end(), x2) - xs.begin();
    y2 = lower_bound(ys.begin(), ys.end(), y2) - ys.begin();
    for (int x = x1; x < x2; ++x) for (int y = y1; y < y2; ++y) B[x][y] = i + 1;
  }

  vector<int> area(N + 1);
  for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) {
    if (B[i][j] == 0) continue;
    int x1 = xs[i], y1 = ys[j], x2 = xs[i + 1], y2 = ys[j + 1];
    area[B[i][j]] += (x2 - x1) * (y2 - y1);
  }

  vector<pii> area_s;
  for (int i = 1; i <= N; ++i) area_s.emplace_back(area[i], -i);
  sort(area_s.begin(), area_s.end());

  vector<int> ans;
  while (K--) {
    auto [_, i] = area_s.back(); area_s.pop_back();
    ans.push_back(-i);
  }
  sort(ans.begin(), ans.end());
  for (int e : ans) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
