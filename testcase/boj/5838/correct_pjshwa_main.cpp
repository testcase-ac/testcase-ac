#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;
  vector<tuple<int, int, int, int, int>> R;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    R.emplace_back(x1, y1, y2, 1, i);
    R.emplace_back(x2, y1, y2, -1, i);
  }
  sort(R.begin(), R.end());

  set<pii> ys; int ans = N;
  vector<int> vis(N, 0);
  for (int i = 0; i < 2 * N; ++i) {
    auto [cx, cy1, cy2, o, idx] = R[i];
  
    if (o == 1) {
      auto it = ys.lower_bound({cy2, -INF});
      if (it != ys.end() && it->second == -1) --ans;
      else {
        vis[idx] = 1;
        ys.insert({cy1, 1});
        ys.insert({cy2, -1});
      }
    }
    else if (vis[idx]) {
      ys.erase(ys.find({cy1, 1}));
      ys.erase(ys.find({cy2, -1}));
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
