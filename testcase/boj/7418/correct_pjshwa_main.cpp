#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, INF = 0x3f3f3f3f;
int N; string S;
int dp[MAXN + 1][MAXN + 1];

bool cmpl(char c1, char c2) {
  if (c1 == '(' && c2 == ')') return true;
  if (c1 == '[' && c2 == ']') return true;
  return false;
}

int rec(int l, int r) {
  if (dp[l][r] != -1) return dp[l][r];
  if (l >= r) return dp[l][r] = l == r;

  int ret = INF;
  if (cmpl(S[l], S[r])) ret = min(ret, rec(l + 1, r - 1));

  for (int p = l; p < r; ++p) {
    ret = min(ret, rec(l, p) + rec(p + 1, r));
  }
  return dp[l][r] = ret;
}

void trace(int l, int r) {
  if (l >= r) {
    if (l == r && dp[l][r] == 1) {
      if (S[l] == '(' || S[l] == ')') cout << "()";
      else cout << "[]";
    }
    return;
  }

  if (cmpl(S[l], S[r]) && dp[l][r] == dp[l + 1][r - 1]) {
    cout << S[l];
    trace(l + 1, r - 1);
    cout << S[r];
  }
  else {
    for (int p = l; p < r; ++p) {
      if (dp[l][r] == dp[l][p] + dp[p + 1][r]) {
        trace(l, p);
        trace(p + 1, r);
        break;
      }
    }
  }
}

void solve() {
  cin >> S; N = S.size();
  memset(dp, -1, sizeof(dp));

  rec(0, N - 1);
  trace(0, N - 1);
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
