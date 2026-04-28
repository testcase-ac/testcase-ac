#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 8, INF = 1e9 + 7;
int b[MAX][MAX], n, m, cnt;
char o[MAX + 1][MAX + 1];

void toggle(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m) return;
  b[x][y] ^= 1;
}

void push(int x, int y) {
  cnt++;
  toggle(x, y);
  toggle(x - 1, y); toggle(x + 1, y); toggle(x, y - 1); toggle(x, y + 1);
  toggle(x - 1, y - 1); toggle(x + 1, y + 1); toggle(x - 1, y + 1); toggle(x + 1, y - 1);
}

void init() {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) b[i][j] = o[i][j] == '*';
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> o[i];

  int mcnt = INF;
  for (int rstate = 0; rstate < (1 << m); rstate++) {
    for (int cstate = 0; cstate < (1 << (n - 1)); cstate++) {
      cnt = 0;
      init();
      for (int j = 0; j < m; j++) if (rstate & (1 << j)) push(0, j);

      for (int i = 1; i < n; i++) {
        if (cstate & (1 << (i - 1))) push(i, 0);

        for (int j = 1; j < m; j++) {
          if (!b[i - 1][j - 1]) push(i, j);
        }
      }

      bool able = true;
      for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (!b[i][j]) able = false;
      if (able) mcnt = min(mcnt, cnt);
    }
  }

  cout << (mcnt == INF ? -1 : mcnt) << '\n';
}
