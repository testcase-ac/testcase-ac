#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1500;
int dp[MAXN][MAXN][5][3];

int get(char c, int w) {
  if (c == '?') {
    if (w == 2) return 2;
    else return w;
  }
  return c - '0';
}

string S;
int rec(int l, int r, int t, int w) {
  if (l > r) return t != 4;
  if (dp[l][r][t][w] != -1) return dp[l][r][t][w];

  int lc = get(S[l], w), rc = get(S[r], w);
  if (t != 4) {
    int pl = (t & 2), pc = (t & 1), ret = !rec(l, r, 4, w);
    if (pl != 0 && lc == pc) ret |= rec(l + 1, r, t, w);
    if (pl == 0 && rc == pc) ret |= rec(l, r - 1, t, w);
    return dp[l][r][t][w] = ret;
  }

  int ret = 0;
  if (w == 2) {
    ret |= !rec(l, r, 4, 0);
    ret |= !rec(l, r, 4, 1);
  }
  if (lc != 2) ret |= rec(l + 1, r, 2 + lc, w);
  if (rc != 2) ret |= rec(l, r - 1, rc, w);

  return dp[l][r][t][w] = ret;
}

void solve() {
  memset(dp, -1, sizeof(dp));
  cin >> S; int w = 0;
  for (char c : S) if (c == '?') w = 2;
  cout << rec(0, (int)S.size() - 1, 4, w) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
