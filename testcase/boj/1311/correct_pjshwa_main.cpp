#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
int a[MAX][MAX];
int d[1 << MAX];
int n;

int dfs(int state, int ix) {
  if (ix == n) return 0;
  if (d[state] != -1) return d[state];

  int ans = INF;
  for (int i = 0; i < n; i++) {
    if (state & (1 << i)) continue;
    int next = state | (1 << i);
    ans = min(ans, dfs(next, ix + 1) + a[ix][i]);
  }

  return d[state] = ans;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  memset(d, -1, sizeof(d));

  cout << dfs(0, 0) << '\n';
}
