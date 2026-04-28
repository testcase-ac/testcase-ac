#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int d[31][8];
int main() {
  fast_io();

  int n;
  cin >> n;

  d[0][7] = 1;
  for (int i = 1; i <= n; i++) {
    d[i][0] = d[i - 1][7];
    d[i][1] = d[i - 1][6];
    d[i][2] = d[i - 1][5];
    d[i][3] = d[i - 1][4] + d[i - 1][7];
    d[i][4] = d[i - 1][3];
    d[i][5] = d[i - 1][2];
    d[i][6] = d[i - 1][1] + d[i - 1][7];
    d[i][7] = d[i - 1][0] + d[i - 1][3] + d[i - 1][6];
  }
  cout << d[n][7] << '\n';
}
