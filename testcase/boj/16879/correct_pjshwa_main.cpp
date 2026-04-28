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

const int MAXN = 3000;
int dp[MAXN][MAXN];

int rec(int i, int j) {
  if (i == 0 && j == 0) return 0;
  if (dp[i][j] != -1) return dp[i][j];

  vector<int> Gs;
  if (i > 0) {
    if (j > 0) Gs.push_back(rec(i - 1, j - 1));
    for (int ni = 0; ni < i; ++ni) Gs.push_back(rec(ni, j));
  }
  if (j > 0) {
    for (int nj = 0; nj < j; ++nj) Gs.push_back(rec(i, nj));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return dp[i][j] = mex;
}

void solve() {
  int N; cin >> N;

  // memset(dp, -1, sizeof dp);
  // for (int x = 0; x < 30; ++x) {
  //   for (int y = 0; y < 30; ++y) {
  //     string res = to_string(rec(x, y));
  //     cout << string(3 - res.size(), ' ') << res;
  //   }
  //   cout << '\n';
  // }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    int xp = x / 3, yp = y / 3, xr = x % 3, yr = y % 3;
    int p = (xp ^ yp) * 3, rs = (xr + yr) % 3;
    ans ^= (p + rs);
  }
  cout << (ans ? "koosaga" : "cubelover") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
