#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[11][11];
int d[10][1 << 10];
int n, m, smax;

bool isSet(int state, int bit) {
  return (1 << bit) & state;
}

bool seatable(int state, int row) {
  for (int j = 0; j < m; j++) {
    if (isSet(state, j)) {
      if (board[row][j] == 'x') return false;
      if (j < m - 1 && isSet(state, j + 1)) return false;
    }
  }
  return true;
}

int main() {
  fast_io();

  int t;
  cin >> t;

  while (t--) {
    cin >> n >> m;
    smax = 1 << m;
    for (int i = 0; i < n; i++) cin >> board[i];
    memset(d, 0, sizeof(d));

    for (int i = 0; i < n; i++) {
      for (int s = 0; s < smax; s++) {
        if (!seatable(s, i)) continue;

        int cnt = 0;
        for (int j = 0; j < m; j++) if (isSet(s, j)) cnt++;

        if (i == 0) d[i][s] = cnt;
        else {
          for (int ps = 0; ps < smax; ps++) {
            if (!seatable(ps, i - 1)) continue;

            bool able = true;
            for (int j = 0; j < m; j++) {
              if (!isSet(s, j)) continue;

              if (j > 0 && isSet(ps, j - 1)) able = false;
              if (j < m - 1 && isSet(ps, j + 1)) able = false;
            }

            if (able) d[i][s] = max(d[i][s], d[i - 1][ps] + cnt);
          }
        }
      }
    }

    cout << *max_element(d[n - 1], d[n - 1] + smax) << '\n';
  }
}
