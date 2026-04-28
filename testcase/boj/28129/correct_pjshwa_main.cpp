#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000, MAXV = 3000, MOD = 1e9 + 7;
int d[MAX + 1][MAXV + 1];

void solve() {
  int N, K; cin >> N >> K;

  for (int i = 1; i <= N; i++) {
    int l, r; cin >> l >> r;
    if (i == 1) {
      for (int j = l; j <= r; j++) d[1][j] = 1;
    }
    else {
      for (int j = l; j <= r; j++) {
        int minx = max(1, j - K), maxx = min(MAXV, j + K);
        d[i][j] = (d[i - 1][maxx] - d[i - 1][minx - 1] + MOD) % MOD;
      }
    }

    for (int j = 1; j <= MAXV; j++) {
      d[i][j] = (d[i][j] + d[i][j - 1]) % MOD;
    }
  }

  cout << d[N][MAXV] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
