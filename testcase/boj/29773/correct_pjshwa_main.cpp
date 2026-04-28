#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S; int N;
ll dp[20][5][2];

ll r(int i, int adv, int f) {
  if (i == N) return adv == 4;
  if (dp[i][adv][f] != -1) return dp[i][adv][f];

  ll ret = 0;
  for (int c = 0; c < 10; c++) {
    if (f && c > S[i] - '0') break;

    int nadv = adv;
    if (
      (adv == 0 && c == 2) || (adv == 1 && c == 0) ||
      (adv == 2 && c == 2) || (adv == 3 && c == 3)
    ) nadv++;
    ret += r(i + 1, nadv, f && c == S[i] - '0');
  }
  return dp[i][adv][f] = ret;
}

void solve() {
  cin >> S; N = S.size();
  memset(dp, -1, sizeof(dp));
  cout << r(0, 0, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
