#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve() {
  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i) {
    string S; cin >> S;
    A[i] = stoi(S.substr(1));
  }

  int T; cin >> T;
  vector<vector<double>> dp(N + 1, vector<double>(T + 1)); dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) for (int t = 0; t <= T; ++t) {
    for (int j = 1; j <= A[i]; ++j) {
      int nt = t + j;
      if (nt > T) break;
      dp[i][nt] += dp[i - 1][t] / A[i];
    }
  }

  cout << fixed << setprecision(5) << dp[N][T] << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
