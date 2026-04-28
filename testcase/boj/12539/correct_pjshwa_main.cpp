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

  int C[13], M; cin >> M;
  for (int i = 1; i <= 12; ++i) cin >> C[i];

  int ans = 0, sm = INT_MAX;
  for (int a = 1; a <= 12; ++a) for (int b = a + 1; b <= 12; ++b) {
    if (C[a] > M) continue;
    int cnt = M / C[a];
    int profit = (C[b] - C[a]) * cnt;
    if (profit > ans) ans = profit, sm = C[a];
    else if (profit == ans) sm = min(sm, C[a]);
  }
  if (sm == INT_MAX) return cout << "IMPOSSIBLE\n", void();

  for (int a = 1; a <= 12; ++a) for (int b = a + 1; b <= 12; ++b) {
    if (C[a] > M) continue;
    int cnt = M / C[a];
    int profit = (C[b] - C[a]) * cnt;
    if (profit == ans && sm == C[a]) {
      cout << a << ' ' << b << ' ' << profit << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
