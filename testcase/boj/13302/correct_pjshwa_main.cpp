#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 1e9 + 7;
ll d[50][MAX + 50];
bool o[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    o[x - 1] = true;
  }

  for (int i = 0; i < MAX + 50; i++) for (int j = 0; j < 50; j++) d[j][i] = INF;
  d[0][0] = 0;

  for (int i = 0; i < n; i++) {
    if (o[i]) {
      for (int j = 0; j < 50; j++) d[j][i + 1] = min(d[j][i + 1], d[j][i]);
    }
    else {
      for (int j = 0; j < 50; j++) d[j][i + 1] = min(d[j][i + 1], d[j][i] + 10000);
      for (int j = 3; j < 50; j++) d[j - 3][i + 1] = min(d[j - 3][i + 1], d[j][i]);
    }

    for (int j = 0; j < 49; j++) d[j + 1][i + 3] = min(d[j + 1][i + 3], d[j][i] + 25000);
    for (int j = 0; j < 48; j++) d[j + 2][i + 5] = min(d[j + 2][i + 5], d[j][i] + 37000);
  }

  ll ans = INF;
  for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) ans = min(ans, d[j][n + i]);
  cout << ans << '\n';
}
