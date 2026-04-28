#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXL = 3e6, INF = 0x3f3f3f3f;
int A[MAXN][MAXN], Li[MAXL];
int N, M, K;

void solve_Ksmall() {
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    for (int j = 0; j < M; ++j) {
      if (S[j] == '.') continue;
      int si = i + 20, sj = j + 20;
      for (int pi = si - K; pi <= si + K; ++pi) for (int pj = sj - K; pj <= sj + K; ++pj) {
        A[pi][pj] = 1;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < MAXN; ++i) for (int j = 0; j < MAXN; ++j) {
    if (A[i][j]) ++ans;
  }
  cout << ans << '\n';
}

void solve_Klarge() {
  char B[N + 1][M + 1];
  for (int i = 0; i < N; ++i) cin >> B[i];

  ll ans = 0, L = 2 * K + 1;
  fill(Li, Li + MAXL, -1);
  for (int j = 0; j < M; ++j) {
    int l = INF, u = -INF;
    for (int i = 0; i < N; ++i) {
      if (B[i][j] == '.') continue;
      l = min(l, i); u = max(u, i);
    }
    if (l == INF) continue;

    for (int i = l; i <= u + 2 * K; ++i) {
      if (Li[i] == -1) ans += L;
      else ans += j - Li[i];
      Li[i] = j;
    }
  }

  cout << ans << '\n';
}

void solve() {
  cin >> N >> M >> K;
  if (K <= 19) solve_Ksmall();
  else solve_Klarge();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
