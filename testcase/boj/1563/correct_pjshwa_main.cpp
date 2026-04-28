#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, MOD = 1e6;
int d[MAX + 1][2][2][2];

void solve() {
  int N;
  cin >> N;

  d[0][0][0][0] = 1;
  for (int i = 1; i <= N; i++) {
    // O
    for (int l = 0; l < 2; l++) for (int p1 = 0; p1 < 2; p1++) for (int p2 = 0; p2 < 2; p2++) {
      d[i][l][p2][0] = (d[i][l][p2][0] + d[i - 1][l][p1][p2]) % MOD;
    }

    // L
    for (int p1 = 0; p1 < 2; p1++) for (int p2 = 0; p2 < 2; p2++) {
      d[i][1][p2][0] = (d[i][1][p2][0] + d[i - 1][0][p1][p2]) % MOD;
    }

    // A
    for (int l = 0; l < 2; l++) for (int p1 = 0; p1 < 2; p1++) for (int p2 = 0; p2 < 2; p2++) {
      if (p1 == 1 && p2 == 1) continue;
      d[i][l][p2][1] = (d[i][l][p2][1] + d[i - 1][l][p1][p2]) % MOD;
    }
  }

  int ans = 0;
  for (int l = 0; l < 2; l++) for (int p1 = 0; p1 < 2; p1++) for (int p2 = 0; p2 < 2; p2++) {
    ans = (ans + d[N][l][p1][p2]) % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
