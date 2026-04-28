#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[20][20];
int rsum[20], csum[20];
int n;

void toggle_row(int i) {
  for (int j = 0; j < n; j++) {
    a[i][j] ? csum[j]-- : csum[j]++;
    a[i][j] ^= 1;
  }
  rsum[i] = n - rsum[i];
}

void toggle_col(int j) {
  for (int i = 0; i < n; i++) {
    a[i][j] ? rsum[i]-- : rsum[i]++;
    a[i][j] ^= 1;
  }
  csum[j] = n - csum[j];
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) {
      a[i][j] = s[j] == 'H' ? 1 : 0;
      rsum[i] += a[i][j];
      csum[j] += a[i][j];
    }
  }

  int mv = 0;
  queue<int> cf;
  for (int state = 0; state < (1 << n); state++) {
    for (int i = 0; i < n; i++) if (state & (1 << i)) toggle_row(i);

    for (int j = 0; j < n; j++) {
      if (csum[j] < n - csum[j]) {
        cf.push(j);
        toggle_col(j);
      }
    }

    mv = max(mv, accumulate(csum, csum + n, 0));

    while (!cf.empty()) {
      toggle_col(cf.front());
      cf.pop();
    }

    for (int i = 0; i < n; i++) if (state & (1 << i)) toggle_row(i);
  }

  cout << n * n - mv;
}
