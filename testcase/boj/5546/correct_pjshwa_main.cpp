#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MOD = 10000;
int P[MAX + 1], d[MAX + 1][4][4];

void solve() {
  int N, K;
  cin >> N >> K;

  memset(P, -1, sizeof(P));
  while (K--) {
    int Ai, Bi;
    cin >> Ai >> Bi;
    P[Ai] = Bi;
  }

  d[0][0][0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int p1 = 0; p1 <= 3; p1++) for (int p2 = 0; p2 <= 3; p2++) for (int nx = 1; nx <= 3; nx++) {
      if (p1 == p2 && p1 == nx) continue;
      if (P[i] != -1 && P[i] != nx) continue;
      d[i][p2][nx] = (d[i][p2][nx] + d[i - 1][p1][p2]) % MOD;
    }
  }

  int ans = 0;
  for (int p1 = 0; p1 <= 3; p1++) for (int p2 = 0; p2 <= 3; p2++) {
    ans += d[N][p1][p2];
    ans %= MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
