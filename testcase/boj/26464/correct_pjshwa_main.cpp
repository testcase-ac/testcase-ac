#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int A[MAXN + 1], dp[MAXN + 1][MAXN + 1];

void solve() {
  int N; cin >> N;

  vector<pii> o;
  for (int i = 1; i <= N; ++i) cin >> A[i], o.emplace_back(A[i], i);
  sort(o.begin(), o.end());

  int ans = 1;
  for (int j = 1; j <= N; ++j) {
    int cres = 1, ores = 1, pa = -1;
    for (auto& [a, i] : o) {
      if (pa != a) cres = ores, pa = a;
      if (i < j) ores = max(ores, dp[i][j]);
      if (i > j) {
        dp[j][i] = cres + 1;
        ans = max(ans, dp[j][i]);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
