#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20, INF = 1e9 + 7;
int a[MAX], b[MAX], d[MAX + 5][2];

int main() {
  fast_io();

  int n, k;
  cin >> n;
  for (int i = 0; i < n - 1; i++) cin >> a[i] >> b[i];
  for (int i = 0; i < n + 5; i++) d[i][0] = d[i][1] = INF;
  cin >> k;

  d[0][0] = d[0][1] = 0;
  for (int i = 0; i < n - 1; i++) {
    d[i + 1][0] = min(d[i + 1][0], d[i][0] + a[i]);
    d[i + 2][0] = min(d[i + 2][0], d[i][0] + b[i]);
    d[i + 1][1] = min(d[i + 1][1], d[i][1] + a[i]);
    d[i + 2][1] = min(d[i + 2][1], d[i][1] + b[i]);
    d[i + 3][1] = min(d[i + 3][1], d[i][0] + k);
  }
  cout << min(d[n - 1][0], d[n - 1][1]) << '\n';
}
