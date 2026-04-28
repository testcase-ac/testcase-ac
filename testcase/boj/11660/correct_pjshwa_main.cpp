#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int board[1025][1025];
int ss[1025][1025];
int main() {
  FastIO();

  int n, m, r1, c1, r2, c2;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> board[i][j];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      ss[i][j] = ss[i][j - 1] + ss[i - 1][j] - ss[i - 1][j - 1] + board[i][j];
    }
  }

  while (m--) {
    cin >> r1 >> c1 >> r2 >> c2;
    cout << ss[r2][c2] - ss[r2][c1 - 1] - ss[r1 - 1][c2] + ss[r1 - 1][c1 - 1] << '\n';
  }
}
