#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MOD = 1e9 + 7;
int dp[MAX + 1][1 << 3];

void solve() {
  int N, R, C; cin >> N >> R >> C;
}

int main() {
  fast_io();

  dp[0][7] = 1;

  // put 1 x 2 or 2 x 1 blocks
  for (int i = 0; i <= MAX; ++i) {
    for (int s = 0; s < 8; ++s) {

    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
