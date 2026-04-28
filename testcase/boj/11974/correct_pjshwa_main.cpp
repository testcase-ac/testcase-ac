#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
int a[MAX], d[MAX][7];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  d[0][a[0] % 7] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 7; j++) {
      if (d[i - 1][j]) d[i][(j + a[i]) % 7] = d[i - 1][j] + 1;
    }
    d[i][a[i] % 7] = max(d[i][a[i] % 7], 1);
  }

  int mx = 0;
  for (int i = 0; i < n; i++) mx = max(mx, d[i][0]);
  cout << mx << '\n';
}
