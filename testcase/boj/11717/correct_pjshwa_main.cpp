#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAXN = 20;
char board[MAXN + 1][MAXN + 1];
int dp[MAXN][MAXN][MAXN][MAXN];

int rec(int i1, int j1, int i2, int j2) {
  if (i1 > i2 || j1 > j2) return 0;
  if (dp[i1][j1][i2][j2] != -1) return dp[i1][j1][i2][j2];

  vector<int> Gs;
  for (int i = i1; i <= i2; ++i) for (int j = j1; j <= j2; ++j) {
    if (board[i][j] == 'X') continue;
    int cur = rec(i1, j1, i - 1, j - 1) ^ rec(i1, j + 1, i - 1, j2)
            ^ rec(i + 1, j1, i2, j - 1) ^ rec(i + 1, j + 1, i2, j2);
    Gs.push_back(cur);
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[i1][j1][i2][j2] = mex;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];
  memset(dp, -1, sizeof(dp));
  cout << (rec(0, 0, N - 1, M - 1) ? "First" : "Second") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
