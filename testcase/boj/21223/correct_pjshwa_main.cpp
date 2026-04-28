#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000, MOD = 1e9 + 7;
int dp[MAXN + 1][MAXN + 1], C[MAXN + 1][MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  map<string, int> U;
  for (int i = 0; i < N; ++i) {
    string s; cin >> s;
    sort(s.begin(), s.end());
    ++U[s];
  }

  vector<int> A;
  for (auto& [s, c] : U) A.push_back(c);
  N = A.size();

  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    int cnt = A[i - 1];
    for (int c = 0; c <= cnt; ++c) {
      ll add = c * (c - 1) / 2, w = C[cnt][c];
      for (int k = add; k <= K; ++k) {
        dp[i][k] = (dp[i][k] + w * dp[i - 1][k - add]) % MOD;
      }
    }
  }
  cout << dp[N][K] << '\n';
}

int main() {
  fast_io();

  C[0][0] = 1;
  for (int i = 1; i <= MAXN; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
