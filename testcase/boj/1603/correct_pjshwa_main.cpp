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

const int MAXN = 10;
char board[MAXN + 1][MAXN + 1];
int R, N, M, dp[MAXN][MAXN];

int rec(int l, int r) {
  if (l > r) return 0;
  if (dp[l][r] != -1) return dp[l][r];
  vector<int> Gs;

  // Fill 1x1
  for (int i = l; i <= r; ++i) {
    int p1 = board[R][i] == '.';
    int p2 = board[R + 1][i] == '.';
    if (!p1 && !p2) continue;

    int g = rec(l, i - 1) ^ rec(i + 1, r);
    if (p1 && p2) g ^= 1;
    Gs.push_back(g);
  }

  // Fill 2x2
  for (int i = l; i < r; ++i) {
    int ok = board[R][i] == '.' && board[R][i + 1] == '.' &&
             board[R + 1][i] == '.' && board[R + 1][i + 1] == '.';
    if (!ok) continue;
    Gs.push_back(rec(l, i - 1) ^ rec(i + 2, r));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[l][r] = mex;
}

void solve() {
  int ans = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  for (R = 0; R < N; R += 2) {
    if (R == N - 1) {
      for (int j = 0; j < M; ++j) ans ^= (board[R][j] == '.');
    } else {
      memset(dp, -1, sizeof dp);
      ans ^= rec(0, M - 1);
    }
  }

  cout << (ans ? "Y" : "M") << '\n';
}

int main() {
  fast_io();

  int t = 3;
  // cin >> t;
  while (t--) solve();
}
