#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
bool d[MAX + 1][MAX + 1];

void solve() {
  int a, b;
  cin >> a >> b;

  d[0][0] = true;
  for (int i = 0; i <= a; i++) for (int j = 0; j <= b; j++) {
    if (i == 0 && j == 0) continue;

    bool bwin = true;
    if (i - 1 >= 0) bwin &= !d[i - 1][j];
    if (j - 1 >= 0) bwin &= !d[i][j - 1];
    if (i - 3 >= 0 && j - 1 >= 0) bwin &= !d[i - 3][j - 1];
    if (i - 1 >= 0 && j - 3 >= 0) bwin &= !d[i - 1][j - 3];
    d[i][j] = bwin;
  }

  cout << (d[a][b] ? "Bob" : "Alice") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
