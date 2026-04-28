#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5 + 50, MAXC = 26, MOD = 1e7;
int B[MAXC][MAXC], L;
int dp[MAXN][MAXC + 1];
string S;

int rec(int i, int j) {
  if (i == L) return 1;
  if (dp[i][j] != -1) return dp[i][j];

  int ret = 0;
  if (j == MAXC) {

  }
  else {
    int u = S[i - MAXC] - 'A';
    for (int v = 0; v < MAXC; v++) {
      if (B[u][v]) continue;
      ret = (ret + rec(v)) % MOD;
    }
  }
}

void solve() {
  int L, M; cin >> L >> S >> M;
  while (M--) {
    string U, V; cin >> U >> V;
    int u = U[0] - 'A', v = V[0] - 'A';
    B[u][v] = 1;
  }

  int ans = 0;
  for (int i = 0; i < L; ++i) ans = (ans + rec(i, MAXC)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
