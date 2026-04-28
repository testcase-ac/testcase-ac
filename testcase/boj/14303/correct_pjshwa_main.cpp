#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4000, MOD = 1e9 + 7;
int dp[MAXN + 5];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int V, Q; cin >> V >> Q;
  vector<string> words;
  for (int i = 0; i < V; ++i) {
    string s; cin >> s;
    sort(s.begin(), s.end());
    words.push_back(s);
  }
  sort(words.begin(), words.end());

  dp[0] = 1;
  while (Q--) {
    string S; cin >> S; int N = S.size();
    fill(dp + 1, dp + N + 1, 0);
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= 20; ++j) {
        if (i - j < 0) break;
        string sub = S.substr(i - j, j);
        sort(sub.begin(), sub.end());

        int cnt = upper_bound(words.begin(), words.end(), sub) -
          lower_bound(words.begin(), words.end(), sub);
        dp[i] = (dp[i] + (ll)dp[i - j] * cnt) % MOD;
      }
    }
    cout << dp[N] << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
