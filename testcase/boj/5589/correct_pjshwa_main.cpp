#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10, MAXM = 1e4;
int A[MAXN][MAXM], C[MAXM];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  int ans = 0;
  for (int s = 0; s < (1 << N); ++s) {
    memset(C, 0, sizeof(C));
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
      int x = A[i][j];
      if (s & (1 << i)) x = 1 - x;
      C[j] += x;
    }

    int cur = 0;
    for (int j = 0; j < M; ++j) cur += max(C[j], N - C[j]);
    ans = max(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
