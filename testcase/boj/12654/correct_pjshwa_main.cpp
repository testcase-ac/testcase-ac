#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXT = 2000, MAXC = 40;
ld dp_p[MAXT + 1][MAXC + 1];
ll dp_c[MAXC + 1][MAXC + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int C, N; cin >> C >> N;
  memset(dp_p, 0, sizeof(dp_p)); dp_p[0][0] = 1;

  ld P = 1.0 / dp_c[C][N];
  for (int t = 1; t <= MAXT; ++t) {
    for (int pcnt = 0; pcnt < C; ++pcnt) {
      for (int ncnt = pcnt; ncnt <= min(C, pcnt + N); ++ncnt) {
        int new_cnt = ncnt - pcnt, old_cnt = N - new_cnt;
        ll ways = dp_c[C - pcnt][new_cnt] * dp_c[pcnt][old_cnt];
        dp_p[t][ncnt] += dp_p[t - 1][pcnt] * ways * P;
      }
    }
  }

  ld ans = 0;
  for (int t = 1; t <= MAXT; ++t) ans += t * dp_p[t][C];
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  dp_c[0][0] = 1;
  for (int i = 1; i <= MAXC; ++i) {
    dp_c[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      dp_c[i][j] = dp_c[i - 1][j - 1] + dp_c[i - 1][j];
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
