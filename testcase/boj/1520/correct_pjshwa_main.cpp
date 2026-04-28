#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
int A[MAXN][MAXN], dp[MAXN][MAXN], N, M;

int rec(int i, int j) {
  if (i == N - 1 && j == M - 1) return 1;
  if (dp[i][j] != -1) return dp[i][j];

  int ret = 0;
  for (int k = 0; k < 4; ++k) {
    int ni = i + dx[k], nj = j + dy[k];
    if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
    if (A[ni][nj] < A[i][j]) ret += rec(ni, nj);
  }
  return dp[i][j] = ret;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
