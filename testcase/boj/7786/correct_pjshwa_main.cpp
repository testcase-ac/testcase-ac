#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S; int N;
ll dp1[10][10][2], dp2[10][10][2];

// count upto n
ll rec1(int i, int c, int f) {
  if (i == N) return 1;
  if (dp1[i][c][f] != -1) return dp1[i][c][f];

  ll ret = 0;
  for (int j = 0; j < 10; j++) {
    if (f && j > S[i] - '0') break;
    ret += rec1(i + 1, j, f && j == S[i] - '0');
  }
  return dp1[i][c][f] = ret;
}

// sum of digits
ll rec2(int i, int c, int f) {
  if (i == N) return 0;
  if (dp2[i][c][f] != -1) return dp2[i][c][f];

  ll ret = 0;
  for (int j = 0; j < 10; j++) {
    if (f && j > S[i] - '0') break;
    ret += rec2(i + 1, j, f && j == S[i] - '0');
    ret += j * rec1(i + 1, j, f && j == S[i] - '0');
  }
  return dp2[i][c][f] = ret;
}

ll upto(int n) {
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  S = to_string(n); N = S.size();
  return rec2(0, 0, 1);
}

void solve() {
  int l, u; cin >> l >> u;

  ll ans = upto(u);
  if (l) ans -= upto(l - 1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
