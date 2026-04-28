#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MOD = 1e9 + 7;
int s[MAX + 1], d[MAX + 1][MAX + 1];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  while (K--) {
    int y, c;
    cin >> y >> c;
    s[y] = c;
  }

  d[0][0] = 1;
  for (int i = 1; i <= M; i++) for (int pc = 0; pc <= N; pc++) {
    if (s[i]) {
      if (pc != s[i]) d[i][s[i]] = (d[i][s[i]] + d[i - 1][pc]) % MOD;
    }
    else {
      for (int nc = 1; nc <= N; nc++) {
        if (pc == nc) continue;
        d[i][nc] = (d[i][nc] + d[i - 1][pc]) % MOD;
      }
    }
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) ans = (ans + d[M][i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
