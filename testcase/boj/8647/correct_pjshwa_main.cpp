#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  int maxh[2]{}, rcnt = 0, ccnt = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < N; ++i) {
    int h; cin >> h;
    pq.push({h, 0});
  }
  for (int i = 0; i < M; ++i) {
    int h; cin >> h;
    pq.push({h, 1});
  }

  ll ans = 0;
  while (!pq.empty()) {
    auto [h, d] = pq.top(); pq.pop();
    if (d == 0) {
      if (h > maxh[1] && ccnt == M) return cout << "NIE\n", void();
      maxh[0] = max(maxh[0], h); ++rcnt;
      ans += (ll)h * (M - ccnt);
    } else {
      if (h > maxh[0] && rcnt == N) return cout << "NIE\n", void();
      maxh[1] = max(maxh[1], h); ++ccnt;
      ans += (ll)h * (N - rcnt);
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
