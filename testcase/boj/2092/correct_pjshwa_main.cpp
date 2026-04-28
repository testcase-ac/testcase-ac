#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4000, MAXV = 200, MOD = 1e6;
int t[MAXV + 1], d[MAXV + 1][MAXN + 1];

void solve() {
  int T, A, S, B;
  cin >> T >> A >> S >> B;
  for (int i = 1; i <= A; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  d[0][0] = 1;
  for (int i = 1; i <= T; i++) {
    for (int v = 0; v <= A; v++) for (int u = 0; u <= t[i]; u++) {
      int w = v + u;
      if (w > A) break;
      d[i][w] = (d[i][w] + d[i - 1][v]) % MOD;
    }
  }
  
  int ans = 0;
  for (int i = S; i <= B; i++) ans = (ans + d[T][i]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
