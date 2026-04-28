#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e9 + 7;
int o[19][19], b[19][19], n, cnt;

void toggle(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= n) return;
  b[x][y] ^= 1;
}

void push(int x, int y) {
  cnt++;
  toggle(x, y); toggle(x - 1, y); toggle(x + 1, y); toggle(x, y - 1); toggle(x, y + 1);
}

void init() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) b[i][j] = o[i][j];
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> o[i][j];

  int mcnt = MAX;
  for (int state = 0; state < (1 << n); state++) {
    cnt = 0;
    init();
    for (int j = 0; j < n; j++) if (state & (1 << j)) push(0, j);

    for (int i = 1; i < n; i++) for (int j = 0; j < n; j++) {
      if (b[i - 1][j]) push(i, j);
    }

    bool able = true;
    for (int j = 0; j < n; j++) if (b[n - 1][j]) able = false;
    if (able) mcnt = min(mcnt, cnt);
  }

  cout << (mcnt == MAX ? -1 : mcnt);
}
