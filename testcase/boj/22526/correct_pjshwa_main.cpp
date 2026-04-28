#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 16, INF = 1e9 + 7;
int a[MAX][MAX + 1], d[1 << MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
void solve() {
  for (int i = 0; i < n; i++) for (int j = 0; j <= n; j++) cin >> a[i][j];

  fill(d, d + (1 << n), INF);
  d[0] = 0;
  for (int state = 1; state < (1 << n); state++) {

    for (int cur = 0; cur < n; cur++) {
      if ((state & (1 << cur)) == 0) continue;

      d[state] = min(d[state], d[state - (1 << cur)] + a[cur][0]);
      for (int sel = 0; sel < n; sel++) {
        if ((state & (1 << sel)) == 0 || cur == sel) continue;

        d[state] = min(d[state], d[state - (1 << cur)] + a[cur][sel + 1]);
      }
    }

  }

  cout << d[(1 << n) - 1] << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
