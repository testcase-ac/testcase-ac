#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int d[MAX + 1][10];

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int j = 0; j <= 9; ++j) ans = (ans + d[N][j]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int j = 0; j <= 9; ++j) d[1][j] = 1;
  for (int i = 2; i <= MAX; ++i) {
    for (int pj = 0; pj <= 9; ++pj) for (int nj = pj; nj <= 9; ++nj) {
      d[i][nj] = (d[i][nj] + d[i - 1][pj]) % MOD;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
