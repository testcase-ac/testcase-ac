#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, MAXV = 3e5, INF = 0x3f3f3f3f;
const int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1}, dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
int A[MAX][MAX], d[MAX][MAX];
int T[MAXV + 1];
int N, M;

int dfs(int i, int j) {
  if (d[i][j] != -1) return d[i][j];

  int ret = A[i][j], mval = INF;
  for (int k = 0; k < 8; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= N || y < 0 || y >= M) continue;
    if (A[x][y] < A[i][j]) mval = min(mval, A[x][y]);
  }
  for (int k = 0; k < 8; k++) {
    int x = i + dx[k], y = j + dy[k];
    if (x < 0 || x >= N || y < 0 || y >= M) continue;
    if (A[x][y] == mval) ret = min(ret, dfs(x, y));
  }
  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  memset(d, -1, sizeof(d));
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    T[dfs(i, j)]++;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) cout << T[A[i][j]] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
