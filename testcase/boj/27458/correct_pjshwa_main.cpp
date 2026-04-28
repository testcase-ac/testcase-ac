#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S; int N;
ll dp[20][4][2];

ll rec(int i, int o, int f) {
  if (dp[i][o][f] != -1) return dp[i][o][f];
  if (i == N) return o == 3;

  ll ret = 0;
  for (int c = 0; c < 10; ++c) {
    if (f && c > S[i] - '0') break;
    if (o == 3) ret += rec(i + 1, 3, f && c == S[i] - '0');
    else {
      int no = c == 6 ? o + 1 : 0;
      ret += rec(i + 1, no, f && c == S[i] - '0');
    }
  }
  return dp[i][o][f] = ret;
}

void solve() {
  cin >> S; N = S.size();

  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
