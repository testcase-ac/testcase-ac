#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
int B[MAXN + 1][MAXN + 1], P[MAXN + 1][MAXN + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int M, N; cin >> M >> N;
  for (int i = 1; i <= N; ++i) {
    string S; cin >> S;
    for (int j = 1; j <= M; ++j) {
      char c = S[j - 1];
      B[i][j] = c == 'G' || c == 'S';
    }
  }
  for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
    P[i][j] = B[i][j] + P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
  }

  int ans = 0;
  for (int i1 = 1; i1 <= N; ++i1) for (int j1 = 1; j1 <= M; ++j1) 
  for (int i2 = i1; i2 <= N; ++i2) for (int j2 = j1; j2 <= M; ++j2) {
    int cnt = P[i2][j2] - P[i1 - 1][j2] - P[i2][j1 - 1] + P[i1 - 1][j1 - 1];
    if (cnt == (i2 - i1 + 1) * (j2 - j1 + 1)) ans = max(ans, cnt);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
