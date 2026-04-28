#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
int d[MAX + 1];
pii s[MAX];

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    s[i] = {x, y};
  }

  for (int w = 0; w <= MAX; w++) d[w] = INF;
  d[0] = 0;

  for (int w = 0; w <= MAX; w++) {
    for (int i = 0; i < n; i++) {
      auto [x, y] = s[i];
      if (w + y <= MAX) d[w + y] = min(d[w + y], d[w] + x);
    }
  }

  cout << d[m] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
