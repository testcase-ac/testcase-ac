#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXV = 200, INF = 0x3f3f3f3f;
int A[MAX][2], d[MAX][MAXV + 1];
int N;

int r(int i, int v) {
  if (d[i][v] != -1) return d[i][v];
  if (i == N - 1) return d[i][v] = 0;

  int s = A[i + 1][0], e = A[i + 1][1], ret = INF;
  for (int j = s; j <= e; j++) {
    ret = min(ret, r(i + 1, j) + abs(v - j));
  }
  return d[i][v] = ret;
}

void trace(int i, int v) {
  cout << v << '\n';
  if (i == N - 1) return;

  int s = A[i + 1][0], e = A[i + 1][1], ret = INF, nv = -1;
  for (int j = s; j <= e; j++) {
    if (d[i][v] == d[i + 1][j] + abs(v - j)) {
      trace(i + 1, j);
      return;
    }
  }
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < 2; j++) cin >> A[i][j];

  memset(d, -1, sizeof(d));
  int ans = INF;
  for (int j = A[0][0]; j <= A[0][1]; j++) ans = min(ans, r(0, j));

  cout << ans << '\n';
  for (int j = A[0][0]; j <= A[0][1]; j++) {
    if (d[0][j] == ans) {
      trace(0, j);
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
