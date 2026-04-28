#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
char board1[MAX + 1][MAX + 1], board2[MAX + 1][MAX + 1];
int P[MAX + 1][MAX + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> board1[i];
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if ((i + j) & 1) board2[i][j] = 'W';
    else board2[i][j] = 'B';
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    P[i][j] = board1[i - 1][j - 1] == board2[i - 1][j - 1];
    P[i][j] += P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
  }

  int ans = N * M;
  for (int i = K; i <= N; i++) for (int j = K; j <= M; j++) {
    int cnt = P[i][j] - P[i - K][j] - P[i][j - K] + P[i - K][j - K];
    ans = min({ans, cnt, K * K - cnt});
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
