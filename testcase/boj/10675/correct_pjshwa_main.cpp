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

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
