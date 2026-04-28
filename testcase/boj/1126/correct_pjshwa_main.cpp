#include <bits/stdc++.h>
#define u(a,b) a=max(a,b)
using namespace std;

const int MAXH = 250'000;
int d[51][MAXH + 1];
int main() {
  int n, s;
  cin >> n;

  memset(d, -1, sizeof(d));
  d[0][0] = 0;

  for (int i = 0; i < n; i++) {
    cin >> s;

    for (int j = 0; j <= MAXH; j++) {
      if (d[i][j] < 0) continue;

      u(d[i + 1][j], d[i][j]);

      if (j + s <= MAXH) u(d[i + 1][j + s], d[i][j] + s);

      if (abs(j - s) <= MAXH) {
        if (j < s) u(d[i + 1][s - j], d[i][j] + s - j);
        else u(d[i + 1][j - s], d[i][j]);
      }
    }
  }

  cout << (d[n][0] ? d[n][0] : -1);
}
