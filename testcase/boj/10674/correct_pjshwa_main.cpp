#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int ab[101][101], ae[101][101];
bool db[101][10001], de[101][10001];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    ab[a][b] = c;
    ae[a][b] = d;
  }

  db[1][0] = de[1][0] = true;
  for (int c = 1; c <= n; c++) {
    for (int k = c + 1; k <= n; k++) {
      if (ab[c][k] == 0) continue;
      for (int l = 0; l <= 10000; l++) {
        if (db[c][l]) db[k][l + ab[c][k]] = true;
      }
    }
  }

  for (int c = 1; c <= n; c++) {
    for (int k = c + 1; k <= n; k++) {
      if (ae[c][k] == 0) continue;
      for (int l = 0; l <= 10000; l++) {
        if (de[c][l]) de[k][l + ae[c][k]] = true;
      }
    }
  }

  for (int l = 0; l <= 10000; l++) {
    if (db[n][l] && de[n][l]) return cout << l, 0;
  }
  cout << "IMPOSSIBLE";
}
