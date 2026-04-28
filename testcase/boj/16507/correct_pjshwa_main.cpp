#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int pic[1001][1001];
int ss[1001][1001];
int main() {
  FastIO();

  int r, c, q, r1, c1, r2, c2;
  cin >> r >> c >> q;
  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      cin >> pic[i][j];
    }
  }

  for (int i = 1; i <= r; i++) {
    for (int j = 1; j <= c; j++) {
      ss[i][j] = ss[i][j - 1] + ss[i - 1][j] - ss[i - 1][j - 1] + pic[i][j];
    }
  }

  int sum, size;
  while (q--) {
    cin >> r1 >> c1 >> r2 >> c2;
    sum = ss[r2][c2] - ss[r2][c1 - 1] - ss[r1 - 1][c2] + ss[r1 - 1][c1 - 1];
    size = (r2 - r1 + 1) * (c2 - c1 + 1);
    cout << sum / size << '\n';
  }
}
