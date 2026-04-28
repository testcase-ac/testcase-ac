#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int a[MAX][3], d[MAX][3];
int n, tc;

void solve() {
  cout << ++tc << ". ";
  for (int i = 0; i < n; i++) {
    cin >> a[i][0] >> a[i][1] >> a[i][2];
    fill(d[i], d[i] + 3, INF);
  }
  
  d[0][1] = a[0][1];
  d[0][2] = a[0][1] + a[0][2];
  for (int i = 1; i < n; i++) {
    d[i][0] = min(d[i - 1][0], d[i - 1][1]) + a[i][0];
    d[i][1] = min({d[i - 1][0], d[i - 1][1], d[i - 1][2], d[i][0]}) + a[i][1];
    d[i][2] = min({d[i - 1][1], d[i - 1][2], d[i][1]}) + a[i][2];
  }

  cout << d[n - 1][1] << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }
}
