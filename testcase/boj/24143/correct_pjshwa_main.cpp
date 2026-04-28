#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> xs, ys;
  for (int i = 0; i < M; ++i) {
    int x, y; cin >> x >> y;
    xs.push_back(x); ys.push_back(y);
  }
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());

  int l = 0, r = 1e9 + 1;
  while (l < r) {
    int m = (l + r) / 2;

    int cnt = 2;
    {
      int last = xs[0];
      for (int i = 1; i < M; ++i) {
        if (xs[i] - last > m) {
          last = xs[i];
          ++cnt;
        }
      }
    }
    {
      int last = ys[0];
      for (int i = 1; i < M; ++i) {
        if (ys[i] - last > m) {
          last = ys[i];
          ++cnt;
        }
      }
    }

    if (cnt <= N) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
