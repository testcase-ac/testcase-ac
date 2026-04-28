#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
bool d[2][MAX + 1];
int w[101];

void solve() {
  int n, e;
  cin >> n >> e;
  for (int i = 1; i <= n; i++) cin >> w[i];

  memset(d, 0, sizeof(d));
  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    int x = i & 1;
    for (int j = 0; j <= 2000 * i; j++) d[x][j] = d[1 - x][j];
    for (int j = w[i]; j <= 2000 * i; j++) {
      d[x][j] |= d[1 - x][j - w[i]];
    }
  }

  for (int j = 0; j <= 2000 * n; j++) {
    if (d[n & 1][j] && j * 2 >= e) {
      cout << j << '\n';
      return;
    }
  }
  cout << "FULL\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
