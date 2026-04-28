#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 16;
int n;
int a[MAX][MAX], h[MAX][MAX], v[MAX][MAX], d[MAX][MAX];

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];

  h[0][1] = 1;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (a[i][j]) continue;
    if (j > 0) {
      h[i][j] += h[i][j - 1];
      h[i][j] += d[i][j - 1];
    }
    if (i > 0) {
      v[i][j] += v[i - 1][j];
      v[i][j] += d[i - 1][j];
    }
    if (i > 0 && j > 0 && a[i - 1][j] == 0 && a[i][j - 1] == 0) {
      d[i][j] += h[i - 1][j - 1];
      d[i][j] += v[i - 1][j - 1];
      d[i][j] += d[i - 1][j - 1];
    }
  }

  cout << h[n - 1][n - 1] + v[n - 1][n - 1] + d[n - 1][n - 1];
}
