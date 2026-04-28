#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<tii> U(K);
  for (auto &[x, y, r] : U) cin >> x >> y >> r;

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    vector<tii> pts;
    bool vis[K] = {};

    for (int k = 0; k < K; k++) {
      auto [x, y, r] = U[k];
      ll d = (ll)r * r - (ll)(x - i) * (x - i);
      if (d < 0) continue;

      ll q = sqrt(d), s, e;
      for (int j = y - q - 1; j <= y - q + 1; j++) {
        if (j < 1 || j > M) continue;
        if ((ll)(y - j) * (y - j) + (ll)(x - i) * (x - i) <= (ll)r * r) {
          s = j;
          break;
        }
      }
      for (int j = y + q + 1; j >= y + q - 1; j--) {
        if (j < 1 || j > M) continue;
        if ((ll)(y - j) * (ll)(y - j) + (ll)(x - i) * (ll)(x - i) <= (ll)r * r) {
          e = j;
          break;
        }
      }

      pts.emplace_back(s, 1, K - k - 1);
      pts.emplace_back(e + 1, -1, K - k - 1);
    }

    sort(pts.begin(), pts.end());
    priority_queue<int, vector<int>, greater<int>> pq;

    int ly = 1;
    for (auto& [y, o, l] : pts) {
      int run = pq.empty() ? K : pq.top();
      ans += (ll)(y - ly) * run;
      ly = y;

      if (o == 1) pq.push(l);
      else vis[l] = true;

      while (!pq.empty()) {
        if (vis[pq.top()]) {
          pq.pop();
          continue;
        }
        else break;
      }
    }
    assert(pq.empty());
    ans += (ll)(M + 1 - ly) * K;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
