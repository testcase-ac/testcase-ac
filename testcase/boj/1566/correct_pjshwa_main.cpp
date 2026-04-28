#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int a[18][18];
int rsum[18], csum[18];
int n, m;

void toggle_row(int i) {
  for (int j = 0; j < m; j++) {
    a[i][j] = -a[i][j];
    csum[j] = csum[j] + 2 * a[i][j];
  }
  rsum[i] = -rsum[i];
}

void toggle_col(int j) {
  for (int i = 0; i < n; i++) {
    a[i][j] = -a[i][j];
    rsum[i] = rsum[i] + 2 * a[i][j];
  }
  csum[j] = -csum[j];
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      rsum[i] += a[i][j];
      csum[j] += a[i][j];
    }
  }

  int mv = INF;
  queue<int> cf;
  for (int state = 0; state < (1 << n); state++) {
    int rcnt = 0;
    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) {
        rcnt++;
        toggle_row(i);
      }
    }

    bool able = true;
    for (int j = 0; j < m; j++) {
      if (csum[j] == 0) able = false;
      else if (csum[j] < 0) {
        cf.push(j);
        toggle_col(j);
      }
    }
    for (int i = 0; i < n; i++) if (rsum[i] <= 0) able = false;

    if (able) mv = min(mv, rcnt + (int)cf.size());

    while (!cf.empty()) {
      toggle_col(cf.front());
      cf.pop();
    }

    for (int i = 0; i < n; i++) if (state & (1 << i)) toggle_row(i);
  }

  cout << (mv == INF ? -1 : mv);
}
