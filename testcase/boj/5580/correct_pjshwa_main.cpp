#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXV = 2000, MAXS = 3000, MOD = 1e5;
int d[2][MAXV + 1][MAXS + 1];

void solve() {
  int N, M, S;
  cin >> N >> M >> S;

  for (int cval = 0; cval <= M; cval++) d[0][cval][0] = 1;

  for (int i = 1; i <= N * N; i++) {
    int x = i & 1;
    memset(d[x], 0, sizeof(d[x]));

    for (int cval = 1; cval <= M; cval++) for (int psum = 0; psum <= S; psum++) {
      if (psum + cval > S) break;
      d[x][cval][psum + cval] = (d[x][cval][psum + cval] + d[1 - x][cval - 1][psum]) % MOD;
    }

    for (int cval = 1; cval <= M; cval++) for (int psum = 0; psum <= S; psum++) {
      d[x][cval][psum] = (d[x][cval][psum] + d[x][cval - 1][psum]) % MOD;
    }
  }

  cout << d[(N * N) & 1][M][S] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
