#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40;
ll dp[MAXN];

void solve() {
  int A, B, N; cin >> A >> B >> N;
  vector<int> S = {0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000};
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    S.push_back(x);
  }
  sort(S.begin(), S.end());

  N = S.size(); dp[0] = 1;
  for (int i = 1; i < N; ++i) for (int j = 0; j < i; ++j) {
    int d = S[i] - S[j];
    if (d < A || d > B) continue;
    dp[i] += dp[j];
  }
  cout << dp[N - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
