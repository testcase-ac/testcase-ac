#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 100, INF = 1e18;
ll d[MAX + 1][MAX + 1], A[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;
  while (M--) {
    int x; cin >> x;
    A[x] = 1;
  }

  for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++) d[i][j] = INF;
  d[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    if (A[i]) {
      for (int j = 0; j <= N; j++) d[i][0] = min(d[i][0], d[i - 1][j]);
    }
    d[i][1] = d[i - 1][0] + 7;
    for (int j = 2; j <= N; j++) d[i][j] = d[i - 1][j - 1] + 2;
  }

  ll ans = INF;
  for (int i = 0; i <= N; i++) ans = min(ans, d[N][i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
