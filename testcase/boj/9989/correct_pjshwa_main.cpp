#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20;
vector<pii> B[MAXN + 1];

// max score obtained by cows set in the first x events
int dp[1 << MAXN], S[MAXN][MAXN];

void solve() {
  int N, b; cin >> N >> b;
  while (b--) {
    int k, p, a; cin >> k >> p >> a;
    B[k].emplace_back(p, a);
  }
  for (int k = 0; k <= MAXN; ++k) sort(B[k].begin(), B[k].end());
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> S[i][j];

  for (int s = 1; s < (1 << N); ++s) {
    int cnt = __builtin_popcount(s);
    for (int i = 0; i < N; ++i) {
      if (!(s & (1 << i))) continue;

      // cow i will perform at cnt-th event
      dp[s] = max(dp[s], dp[s ^ (1 << i)] + S[i][cnt - 1]);
    }
    for (auto& [p, a] : B[cnt]) {
      if (dp[s] >= p) dp[s] += a;
    }
  }

  cout << dp[(1 << N) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
