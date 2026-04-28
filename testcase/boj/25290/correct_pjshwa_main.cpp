#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, K; cin >> N >> K;
  if (K < N - 1 || (K & 1)) return cout << "IMPOSSIBLE\n", void();

  int udiff = N * N - 1 - K;
  int mdiff = N * N - (N - 2) * (N - 2) - 1;

  int p1 = 2, p2 = 2 + mdiff, it = 4, dif = mdiff + 1, add = N - 1;
  auto next = [&]() {
  
    p1 += add;
    dif -= 2;
    p2 = p1 + dif - 1;

    it--;
    if (it == 0) {
      add -= 2;
      it = 4;
    }
  };

  vector<pii> ans;
  while (udiff > 0) {
    if (udiff >= dif - 2) {
      udiff -= (dif - 2);
      ans.emplace_back(p1, p2);
      for (int i = 0; i < 4; i++) next();
    }
    else next();
  }

  cout << ans.size() << '\n';
  for (auto& [x, y] : ans) cout << x << ' ' << y << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
