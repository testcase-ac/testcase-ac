#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000, INF = 1e9 + 7;
int S[MAX + 1], d[MAX + 1][101], N, M;

int r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == 0) return d[i][j] = 0;

  int res = -INF;
  for (int l = 0; l < M; l++) {
    if (i < j * S[l]) continue;

    int pre = r(i - j * S[l], j + 1);
    if (pre == -INF) continue;

    res = max(res, pre + S[l]);
  }

  return d[i][j] = res;
}

void solve() {
  cin >> N >> M;
  for (int i = 0; i < M; i++) cin >> S[i];

  memset(d, -1, sizeof(d));

  int ans = r(N, 1);
  if (ans == -INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
