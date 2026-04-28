#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, k, s;
int d[21][11][156];
void solve() {
  cout << d[n][k][s] << '\n';
}

int main() {
  fast_io();

  for (int state = 0; state < (1 << 20); state++) {
    int ck = __builtin_popcount(state);
    if (ck > 10) continue;

    int mval = 0, csum = 0;
    for (int i = 0; i < 20; i++) {
      if (state & (1 << i)) {
        mval = max(mval, i + 1);
        csum += (i + 1);
      }
    }

    if (csum > 155) continue;
    for (int i = mval; i <= 20; i++) d[i][ck][csum]++;
  }

  while (1) {
    cin >> n >> k >> s;
    if (n == 0 && k == 0 && s == 0) break;
    solve();
  }
}
