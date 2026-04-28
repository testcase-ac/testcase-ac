#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int dp[MAXN + 1][2];

void solve() {
  int N, Acnt, Bcnt, p, i = 0; cin >> N >> Acnt >> Bcnt;
  set<int> P, A, B;
  for (int i = 0; i < Acnt; ++i) {
    cin >> p;
    P.insert(p); A.insert(p);
  }
  for (int i = 0; i < Bcnt; ++i) {
    cin >> p;
    P.insert(p); B.insert(p);
  }
  N = P.size(); memset(dp, 0x3f, sizeof(dp));
  for (int p : P) {
    if (i == 0) {
      if (A.count(p)) dp[i][0] = 0;
      if (B.count(p)) dp[i][1] = 0;
    } else {
      if (A.count(p)) dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + 1);
      if (B.count(p)) dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + 1);
    }
    ++i;
  }

  int ans = min(dp[N - 1][0], dp[N - 1][1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
