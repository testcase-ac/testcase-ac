#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 5000, INF = 1e18;

// d[i][j][k]: minimum penalty when..
// i: passing i th obstacle
// j: index that method not lastly used was used
// k: method last used
ll d[MAX + 1][MAX + 1][2];
int T[MAX + 1], S[MAX + 1];

void solve() {
  int N, A, B, X, Y; cin >> N >> A >> B >> X >> Y;
  for (int i = 1; i <= N; i++) cin >> T[i] >> S[i];

  for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++) d[i][j][0] = d[i][j][1] = INF;
  if (S[1] == 1 || S[1] == 3) d[1][0][0] = X;
  if (S[1] == 2 || S[1] == 3) d[1][0][1] = Y;

  for (int i = 2; i <= N; i++) {
    if (S[i] == 1 || S[i] == 3) {
      if (T[i] - T[i - 1] >= A) {
        for (int t = 0; t <= i; t++) {
          d[i][t][0] = min(d[i][t][0], d[i - 1][t][0] + X);
        }
      }

      d[i][i - 1][0] = min(d[i][i - 1][0], d[i - 1][0][1] + X);
      for (int t = 1; t <= i; t++) {
        if (T[i] - T[t] < A) break;
        d[i][i - 1][0] = min(d[i][i - 1][0], d[i - 1][t][1] + X);
      }
    }
    if (S[i] == 2 || S[i] == 3) {
      if (T[i] - T[i - 1] >= B) {
        for (int t = 0; t <= i; t++) {
          d[i][t][1] = min(d[i][t][1], d[i - 1][t][1] + Y);
        }
      }

      d[i][i - 1][1] = min(d[i][i - 1][1], d[i - 1][0][0] + Y);
      for (int t = 1; t <= i; t++) {
        if (T[i] - T[t] < B) break;
        d[i][i - 1][1] = min(d[i][i - 1][1], d[i - 1][t][0] + Y);
      }
    }
  }

  ll ans = INF;
  for (int t = 0; t <= N; t++) ans = min({ans, d[N][t][0], d[N][t][1]});

  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
