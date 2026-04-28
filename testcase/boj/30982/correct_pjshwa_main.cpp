#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXV = 100000, INF = 0x3f3f3f3f;
int A[MAXN];
int dp_l[MAXN][MAXV + 1], dp_r[MAXN][MAXV + 1];

void solve() {
  int N, M, T, P; cin >> N >> M >> T;
  for (int i = 0; i < N; ++i) cin >> A[i];
  cin >> P; --P;
  M -= A[P];

  memset(dp_l, 0x3f, sizeof(dp_l));
  memset(dp_r, 0x3f, sizeof(dp_r));

  dp_l[P][0] = 0;
  for (int i = P - 1; i >= 0; --i) {
    for (int j = 0; j <= MAXV; ++j) dp_l[i][j] = dp_l[i + 1][j];
    for (int j = A[i]; j <= MAXV; ++j) {
      if (dp_l[i + 1][j - A[i]] == INF) continue;
      dp_l[i][j] = min(dp_l[i][j], P - i);
    }
  }

  dp_r[P][0] = 0;
  for (int i = P + 1; i < N; ++i) {
    for (int j = 0; j <= MAXV; ++j) dp_r[i][j] = dp_r[i - 1][j];
    for (int j = A[i]; j <= MAXV; ++j) {
      if (dp_r[i - 1][j - A[i]] == INF) continue;
      dp_r[i][j] = min(dp_r[i][j], i - P);
    }
  }

  int ans = INF;
  for (int l = 0; l <= M; ++l) {
    if (dp_l[0][l] == INF) continue;
    if (dp_r[N - 1][M - l] == INF) continue;

    int dis = min(dp_l[0][l], dp_r[N - 1][M - l]);
    dis += dp_l[0][l] + dp_r[N - 1][M - l];

    ans = min(ans, dis);
  }

  if (ans > T) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
