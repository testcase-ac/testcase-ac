#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[51][51];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; i++) cin >> board[i];

  int mncnt = 1e9, cnt;
  for (int i = 0; i < n - 7; i++) {
    for (int j = 0; j < m - 7; j++) {
      cnt = 0;
      for (int k = i; k < i + 8; k++) {
        for (int s = j; s < j + 8; s++) {
          if (
            ((k + s - i - j) & 1) && board[k][s] == 'W' ||
            ((k + s - i - j) & 1) == 0 && board[k][s] == 'B'
          ) cnt++;
        }
      }
      mncnt = min(mncnt, cnt);
    }
  }

  for (int i = 0; i < n - 7; i++) {
    for (int j = 0; j < m - 7; j++) {
      cnt = 0;
      for (int k = i; k < i + 8; k++) {
        for (int s = j; s < j + 8; s++) {
          if (
            ((k + s - i - j) & 1) && board[k][s] == 'B' ||
            ((k + s - i - j) & 1) == 0 && board[k][s] == 'W'
          ) cnt++;
        }
      }
      mncnt = min(mncnt, cnt);
    }
  }

  cout << mncnt << '\n';
}
