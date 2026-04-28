#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, N, T; cin >> L >> N >> T;

  vector<pii> balls(N);
  for (int i = 0; i < N; i++) {
    int p; string o; cin >> p >> o;
    if (o == "L") balls[i] = {p, -1};
    else balls[i] = {p, 1};
  }

  auto tick = [&]() {
    for (int i = 0; i < N; i++) {
      balls[i].first += balls[i].second;
      if (balls[i].first == 0 || balls[i].first == L) balls[i].second *= -1;
    }
  };

  int ans = 0;
  for (int t = 1; t <= T; t++) {
    tick();

    map<int, int> cpos;
    for (int i = 0; i < N; i++) cpos[balls[i].first]++;

    for (auto& [_, v] : cpos) {
      if (v >= 2) ans++;
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
