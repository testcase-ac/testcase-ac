#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int d[MAX + 1];
int v[20], w[20];

int main() {
  fast_io();

  int c, n;
  cin >> c >> n;
  for (int i = 0; i < n; ++i) cin >> w[i] >> v[i];

  for (int j = 0; j <= MAX; ++j) for (int i = 0; i < n; ++i) {
    if (j + w[i] <= MAX) d[j + w[i]] = max(d[j + w[i]], d[j] + v[i]);
  }

  for (int j = 0; j <= MAX; ++j) {
    if (d[j] >= c) return cout << j << '\n', 0;
  }
}
