#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
const int dx[3] = {0, 1, -1};
bool dp[MAXN][MAXN + 1][2];
int L[MAXN], R[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> L[i] >> R[i];

  for (int s = 0; s <= MAXN; ++s) {
    int d = s < L[0] || s > R[0];
    dp[0][s][d] = true;
  }

  auto oob = [&](int x) {
    return x < 0 || x > MAXN;
  };
  for (int i = 1; i < N; ++i) for (int pp = 0; pp <= MAXN; ++pp) for (int k = 0; k < 3; ++k) {
    int np = pp + dx[k];
    if (oob(np)) continue;

    int d = np < L[i] || np > R[i];
    for (int pd = 0; pd < 2; ++pd) {
      int nd = pd + d;
      if (nd > 1) continue;
      if (dp[i - 1][pp][pd]) dp[i][np][nd] = true;
    }
  }

  for (int p = 0; p <= MAXN; ++p) for (int d = 0; d < 2; ++d) {
    if (dp[N - 1][p][d]) return cout << "World Champion\n", void();
  }
  cout << "Surrender\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
