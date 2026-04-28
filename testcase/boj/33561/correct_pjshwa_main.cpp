#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
ll B[MAXN + 1][MAXN + 1], Z[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
    cin >> B[i][j];
    Z[i][j] = Z[i - 1][j] + Z[i][j - 1] - Z[i - 1][j - 1] + (B[i][j] == 0);
    B[i][j] = B[i - 1][j] + B[i][j - 1] - B[i - 1][j - 1] + B[i][j];
  }

  int K; cin >> K;
  vector<int> P(K + 1);
  for (int i = 1; i <= K; ++i) cin >> P[i];
  sort(P.begin() + 1, P.end(), greater<int>());
  for (int i = 1; i <= K; ++i) P[i] += P[i - 1];

  ll ans = 0;
  for (int d = 1; d <= N; ++d) for (int i = 1; i + d - 1 <= N; ++i) for (int j = 1; j + d - 1 <= N; ++j) {
    int x = i + d - 1, y = j + d - 1;
    ll sum = B[x][y] - B[i - 1][y] - B[x][j - 1] + B[i - 1][j - 1];
    ll zcnt = Z[x][y] - Z[i - 1][y] - Z[x][j - 1] + Z[i - 1][j - 1];
    if (zcnt <= K) ans = max(ans, sum + P[zcnt]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
