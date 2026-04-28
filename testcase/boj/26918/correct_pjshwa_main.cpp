#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int dp[MAXN + 1][MAXN + 1];

int rec(int w, int h) {
  if (dp[w][h] != -1) return dp[w][h];
  if (w == 1 && h == 1) return dp[w][h] = 0;

  int ret = 0;
  for (int nw = 1; nw < w; ++nw) {
    ret |= (rec(nw, h) == 0 && rec(w - nw, h) == 0);
  }
  for (int nh = 1; nh < h; ++nh) {
    ret |= (rec(w, nh) == 0 && rec(w, h - nh) == 0);
  }
  return dp[w][h] = ret;
}

void solve() {
  int N, M; cin >> N >> M;

  memset(dp, -1, sizeof(dp));
  if (rec(N, M)) cout << "A\n";
  else cout << "B\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
