#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 2e5, BIAS = 1e5;

void solve() {
  int N; cin >> N;
  vector<pii> points;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    points.emplace_back(x + BIAS, y + BIAS);
  }

  map<int, vector<int>> X, Y;
  for (auto& [x, y] : points) {
    X[x].push_back(y);
    Y[y].push_back(x);
  }
  for (auto& [_, v] : X) sort(v.begin(), v.end());
  for (auto& [_, v] : Y) sort(v.begin(), v.end());

  ll ans = 0;
  for (auto& [x, y] : points) {
    ll xl = lower_bound(X[x].begin(), X[x].end(), y) - X[x].begin();
    ll yl = lower_bound(Y[y].begin(), Y[y].end(), x) - Y[y].begin();
    ll xr = X[x].size() - xl - 1, yr = Y[y].size() - yl - 1;
    ans += 2 * xl * xr * yl * yr;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
