#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;
const int req[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int d[MAX + 1];

void solve() {
  int n;
  cin >> n;

  fill(d, d + MAX + 1, -INF);
  d[0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 10; j++) {
      if (i - req[j] >= 0) d[i] = max(d[i], d[i - req[j]] + j);
    }
  }

  cout << d[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
