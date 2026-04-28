#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
map<int, int> routes[MAXN];
int costs[MAXN];

void solve() {
  int A, B, N; cin >> A >> B >> N;
  for (int r = 0; r < N; ++r) {
    int s; cin >> costs[r] >> s;
    for (int i = 0; i < s; ++i) {
      int x; cin >> x;
      routes[r][x] = i;
    }
  }
  if (A == B) return cout << "0\n", void();

  // use 1 route
  int ans = INF;
  for (int r = 0; r < N; ++r) {
    if (!routes[r].count(A) || !routes[r].count(B)) continue;
    int ai = routes[r][A], bi = routes[r][B];
    if (ai > bi) continue;
    ans = min(ans, costs[r]);
  }

  // use 2 routes
  for (int r1 = 0; r1 < N; ++r1) for (int r2 = 0; r2 < N; ++r2) {
    if (!routes[r1].count(A) || !routes[r2].count(B)) continue;
    int ai = routes[r1][A], bi = routes[r2][B];
    for (auto& [c, ci] : routes[r1]) {
      if (!routes[r2].count(c)) continue;
      int cj = routes[r2][c];
      if (ai > ci || bi < cj) continue;
      ans = min(ans, costs[r1] + costs[r2]);
    }
  }
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
