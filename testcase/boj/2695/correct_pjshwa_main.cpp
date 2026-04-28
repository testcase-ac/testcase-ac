#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int d[1001][51];

void solve() {
  int k, n;
  cin >> k >> n;
  cout << d[n][k] << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAX; i++) d[i][1] = i;
  for (int i = 1; i <= MAX; i++) {
    for (int j = 2; j <= 50; j++) {
      d[i][j] = INF;
      for (int s = 1; s <= i; s++) d[i][j] = min(d[i][j], max(d[s - 1][j - 1], d[i - s][j]) + 1);
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
