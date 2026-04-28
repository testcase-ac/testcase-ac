#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXM = 2000, MOD = 1e9 + 7;
int A[MAXN + 1], L[MAXN + 1], R[MAXN + 1], C[MAXM + 1][MAXM + 1];
vector<int> O;

void dfs(int v) {
  if (L[v] != -1) dfs(L[v]);
  O.push_back(A[v]);
  if (R[v] != -1) dfs(R[v]);
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> A[i] >> L[i] >> R[i];
  dfs(1); O.push_back(M + 1);

  C[0][0] = 1;
  for (int i = 1; i <= M; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }

  int low = 1, streak = 0, ans = 1;
  for (int i = 0; i <= N; ++i) {
    if (O[i] == -1) ++streak;
    else {
      if (streak > 0) {
        ans = ((ll)ans * C[O[i] - low][streak]) % MOD;
        streak = 0;
      }
      low = O[i] + 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
