#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, A, B; cin >> N >> A >> B;

  vector<pii> V(N);
  for (int i = 0; i < N; ++i) cin >> V[i].first >> V[i].second;
  sort(V.begin(), V.end(), [](pii& a, pii& b) {
    auto [ax, ay] = a; auto [bx, by] = b;
    return ax - ay > bx - by;
  });

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    auto [x, y] = V[i];
    if (i < B) ans += y;
    else ans += x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
