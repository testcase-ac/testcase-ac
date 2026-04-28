#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 100, INF = 1e18;
const int dy[3] = {-1, 0, 1}, dx[3] = {-1, -1, -1};
int A[MAX][MAX], B[MAX][MAX];
ll d[MAX][MAX];

ll score(int i, int j) {
  return (B[i][j] - A[i][j]) * (B[i][j] - A[i][j]);
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> B[i][j];

  for (int i = 0; i < N; i++) fill(d[i], d[i] + M, INF);
  for (int j = 0; j < M; j++) d[0][j] = score(0, j);
  for (int i = 1; i < N; i++) for (int j = 0; j < M; j++) {
    for (int k = 0; k < 3; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || nj < 0 || nj >= M) continue;
      d[i][j] = min(d[i][j], d[ni][nj] + score(i, j));
    }
  }

  ll ans = INF;
  for (int j = 0; j < M; j++) ans = min(ans, d[N - 1][j]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
