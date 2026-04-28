#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
int hz[MAX][MAX], vz[MAX][MAX];
int d[MAX][MAX][MAX + 10][2];
int N, M;

int r(int ct) {
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int t = 0; t <= ct; t++) d[i][j][t][0] = d[i][j][t][1] = INF;
  }

  for (int t = 0; t <= ct; t++) d[0][0][t][0] = d[0][0][t][1] = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    for (int t = 0; t <= ct; t++) {
      if (j) d[i][j][t][0] = min(d[i][j][t][0], d[i][j - 1][t][0] + hz[i][j - 1]);
      if (j && t) d[i][j][t][0] = min(d[i][j][t][0], d[i][j - 1][t - 1][1] + hz[i][j - 1]);
      if (i) d[i][j][t][1] = min(d[i][j][t][1], d[i - 1][j][t][1] + vz[i - 1][j]);
      if (i && t) d[i][j][t][1] = min(d[i][j][t][1], d[i - 1][j][t - 1][0] + vz[i - 1][j]);
    }
  }

  int ans = INF;
  for (int t = 0; t <= ct; t++) {
    ans = min(ans, min(d[N - 1][M - 1][t][0], d[N - 1][M - 1][t][1]));
  }
  return ans;
}

void solve() {
  int L, G;
  cin >> N >> M >> L >> G;
  for (int i = 0; i < N; i++) for (int j = 0; j < M - 1; j++) cin >> hz[i][j];
  for (int i = 0; i < N - 1; i++) for (int j = 0; j < M; j++) cin >> vz[i][j];

  // Binary search for # of turns
  int left = 1, right = N + M + 10;
  while (left < right) {
    int mid = (left + right) / 2;
    if (r(mid) <= G) right = mid;
    else left = mid + 1;
  }

  if (left == N + M + 10) cout << "-1\n";
  else cout << (N + M - 2) * L + left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
