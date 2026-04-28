#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, NW; string S; cin >> L >> NW >> S;

  vector<string> dict(NW);
  for (int i = 0; i < NW; i++) cin >> dict[i];

  string dp[L + 1];
  fill(dp, dp + L + 1, "");

  auto covers = [&](int l, string& word) {
    for (int i = l; i < l + word.size(); i++) {
      if (S[i] != '?' && S[i] != word[i - l]) return false;
    }
    return true;
  };

  for (int i = 1; i <= L; i++) {
    for (auto& word : dict) {
      int len = word.length();
      int j = i - len;
      if (j < 0 || j != dp[j].length() || !covers(j, word)) continue;

      if (dp[i].empty()) dp[i] = dp[j] + word;
      else dp[i] = min(dp[i], dp[j] + word);
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
