#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e9 + 7;
int b[15][15], o[15][15], n, m, cnt, mcnt;
string ms, ns;

void toggle(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m) return;
  b[x][y] ^= 1;
}

void push(int x, int y) {
  cnt++; ns[x * m + y] = '1';
  toggle(x, y); toggle(x - 1, y); toggle(x + 1, y); toggle(x, y - 1); toggle(x, y + 1);
}

void init() {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    ns[i * m + j] = '0';
    b[i][j] = o[i][j];
  }
}

int main() {
  fast_io();

  cin >> n >> m;
  ms.resize(n * m, '1');
  ns.resize(n * m);
  mcnt = MAX;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> o[i][j];

  for (int state = 0; state < (1 << m); state++) {
    cnt = 0;
    init();
    for (int j = 0; j < m; j++) if (state & (1 << j)) push(0, j);

    for (int i = 1; i < n; i++) for (int j = 0; j < m; j++) {
      if (b[i - 1][j]) push(i, j);
    }

    bool able = true;
    for (int j = 0; j < m; j++) if (b[n - 1][j]) able = false;
    if (able && mcnt >= cnt) {
      mcnt = cnt;
      if (mcnt > cnt || (mcnt == cnt && ms > ns)) ms = ns;
    }
  }

  if (mcnt == MAX) cout << "IMPOSSIBLE";
  else {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) cout << ms[i * m + j] << ' ';
      cout << '\n';
    }
  }
}
