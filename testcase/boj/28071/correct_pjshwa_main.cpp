#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int u = 0; u <= M; u++) for (int r = 0; r < K; r++) d[u][r] = -INF;
  d[0][0] = 0;

  for (int u = 0; u < M; u++) for (int r = 0; r < K; r++) {
    for (int i = 0; i < N; i++) {
      int nr = (r + A[i]) % K;
      d[u + 1][nr] = max(d[u + 1][nr], d[u][r] + A[i]);
    }
  }

  int ans = 0;
  for (int u = 0; u <= M; u++) ans = max(ans, d[u][0]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
