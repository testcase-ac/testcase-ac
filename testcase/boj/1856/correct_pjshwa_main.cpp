#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int W, L; string S; cin >> W >> L >> S;

  set<string> D;
  for (int i = 0; i < W; i++) {
    string s; cin >> s;
    D.insert(s);
  }

  int dp[L + 1]; dp[0] = 0;
  for (int i = 1; i <= L; i++) {
    dp[i] = dp[i - 1] + 1;
    for (int l = i - 1; l >= i - 25; l--) {
      if (l < 0) break;

      string sub = S.substr(l, i - l);
      cout << "i = " << i << ", l = " << l << ", sub = " << sub << '\n';

      if (D.count(sub)) {
        cout << "found\n";
        dp[i] = min(dp[i], dp[l]);
      }
    }
  }

  cout << dp[L] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
