#include <bits/stdc++.h>
using namespace std;

const int MAX = 100, MOD = 1000000007;
int a[MAX][MAX], d[MAX][MAX];

int main() {
  int r, c, k;
  cin >> r >> c >> k;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> a[i][j];

  d[0][0] = 1;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) {
    for (int k = 0; k < i; k++) for (int l = 0; l < j; l++) {
      if (a[i][j] == a[k][l]) continue;
      d[i][j] = (d[i][j] + d[k][l]) % MOD;
    }
  }

  cout << d[r - 1][c - 1] << '\n';
}
