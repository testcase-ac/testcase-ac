#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX + 1][2], S[MAX + 1][MAX + 1][2];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  int l = 0;
  while (K--) {
    int ai, bi, ci, di;
    cin >> ai >> bi >> ci >> di;

    for (int i = bi; i <= di; i++) S[ai][i][0]++;
    for (int i = ai; i <= ci; i++) S[i][bi][1]++;
    if (ai == 1 && bi == 1) l++;
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    d[i][j][0] = d[i][j][1] = INF;
  }
  d[1][1][0] = d[1][1][1] = l;

  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    if (i == 1 && j == 1) continue;

    if (i > 1) d[i][j][0] = min(d[i - 1][j][0], d[i - 1][j][1]) + S[i][j][0];
    if (j > 1) d[i][j][1] = min(d[i][j - 1][0], d[i][j - 1][1]) + S[i][j][1];
  }

  cout << min(d[N][M][0], d[N][M][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
