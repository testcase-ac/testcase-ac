#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  stack<pii> S;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (i & 1) {
      auto [z, c] = S.top(); S.pop();
      if (x == z || S.empty()) S.push({x, c + 1});
      else {
        auto [y, d] = S.top(); S.pop();
        S.push({y, d + c + 1});
      }
    }
    else {
      if (S.empty() || S.top().first != x) S.push({x, 1});
      else {
        pii top = S.top(); S.pop();
        S.push({x, top.second + 1});
      }
    }
  }

  int ans = 0;
  while (!S.empty()) {
    auto [x, c] = S.top(); S.pop();
    if (x == 0) ans += c;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
