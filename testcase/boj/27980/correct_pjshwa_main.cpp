#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
int d[MAX][MAX];
int N, M; string S, T;

int r(int i, int j) {
  if (j == M) return 0;
  if (d[i][j] != -1) return d[i][j];

  int ret = 0;
  if (i < N - 1) ret = max(ret, r(i + 1, j + 1) + (S[i] == T[j]));
  if (i > 0) ret = max(ret, r(i - 1, j + 1) + (S[i] == T[j]));
  return d[i][j] = ret;
}

void solve() {
  cin >> N >> M >> S >> T;

  memset(d, -1, sizeof(d));
  int ans = 0;
  for (int i = 0; i < N; i++) ans = max(ans, r(i, 0));
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
