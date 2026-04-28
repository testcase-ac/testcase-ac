#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int field[100], cfield[100], vol[20], d[MAX + 1];

int main() {
  fast_io();

  int n, b;
  cin >> n >> b;
  for (int i = 0; i < b; i++) cin >> vol[i];
  for (int i = 0; i < n; i++) cin >> field[i];
  cfield[0] = field[0];
  for (int i = 0; i < n - 1; i++) cfield[i + 1] = field[i + 1] - max(0, field[i] - 1);
  for (int i = 0; i <= MAX; i++) d[i] = INF;

  d[0] = 0;
  for (int i = 1; i <= MAX; i++) {
    for (int j = 0; j < b; j++) {
      if (i - vol[j] >= 0) d[i] = min(d[i], d[i - vol[j]] + 1);
    }
  }

  int tot = 0;
  for (int i = 0; i < n; i++) {
    if (d[cfield[i]] == INF) return cout << -1 << '\n', 0;
    tot += d[cfield[i]];
  }
  cout << tot << '\n';
}
