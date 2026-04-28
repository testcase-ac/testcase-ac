#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  string S; int M; cin >> S >> M;
  int N = S.size();

  vector<string> words(M);
  for (int i = 0; i < M; ++i) cin >> words[i];

  vector<int> dp(N + 1, INF); dp[0] = 0;
  for (int i = 1; i <= N; ++i) {
    for (auto& word : words) {
      int Z = word.size();
      if (Z > i) continue;

      int U[26]{}; bool ok = true;
      for (int j = 0; j < Z; ++j) ++U[word[j] - 'a'];
      for (int j = 0; j < Z; ++j) --U[S[i - Z + j] - 'a'];
      for (int j = 0; j < 26; ++j) if (U[j]) ok = false;
      if (!ok) continue;

      int cost = 0;
      for (int j = 0; j < Z; ++j) if (word[j] != S[i - Z + j]) ++cost;
      dp[i] = min(dp[i], dp[i - Z] + cost);
    }
  }

  cout << (dp[N] == INF ? -1 : dp[N]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
