#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int B[MAXN + 5][MAXN + 5];
int U[MAXN + 5][MAXN + 5], D[MAXN + 5][MAXN + 5];
int L[MAXN + 5][MAXN + 5], R[MAXN + 5][MAXN + 5];
int Us[MAXN + 5][MAXN + 5], Ls[MAXN + 5][MAXN + 5];

void solve() {
  int n, k, pre = 0; cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    string s; cin >> s;
    for (int j = 1; j <= n; ++j) B[i][j] = s[j - 1] == 'W';
  }

  // Fill U, D
  for (int j = 1; j <= n; ++j) {
    U[0][j] = D[n + 1][j] = 1;
    for (int i = 1; i <= n; ++i) U[i][j] = (U[i - 1][j] & B[i][j]);
    for (int i = n; i >= 1; --i) D[i][j] = (D[i + 1][j] & B[i][j]);
  }

  // Fill L, R
  for (int i = 1; i <= n; ++i) {
    L[i][0] = R[i][n + 1] = 1;
    for (int j = 1; j <= n; ++j) L[i][j] = (L[i][j - 1] & B[i][j]);
    for (int j = n; j >= 1; --j) R[i][j] = (R[i][j + 1] & B[i][j]);
  }

  // Fill Us
  for (int j = 1; j <= n; ++j) {
    if (U[n][j]) {
      ++pre;
      continue;
    }
    for (int i = 0; i + k <= n; ++i) Us[i][j] = (U[i][j] & D[i + k + 1][j]);
  }
  for (int i = 0; i + k <= n; ++i) {
    for (int j = 1; j <= n; ++j) Us[i][j] += Us[i][j - 1];
  }

  // Fill Ls
  for (int i = 1; i <= n; ++i) {
    if (L[i][n]) {
      ++pre;
      continue;
    }
    for (int j = 0; j + k <= n; ++j) Ls[i][j] = (L[i][j] & R[i][j + k + 1]);
  }
  for (int j = 0; j + k <= n; ++j) {
    for (int i = 1; i <= n; ++i) Ls[i][j] += Ls[i - 1][j];
  }

  int ans = 0;
  for (int i = 1; i + k - 1 <= n; ++i) for (int j = 1; j + k - 1 <= n; ++j) {
    int ucnt = Us[i - 1][j + k - 1] - Us[i - 1][j - 1];
    int lcnt = Ls[i + k - 1][j - 1] - Ls[i - 1][j - 1];
    ans = max(ans, ucnt + lcnt + pre);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
