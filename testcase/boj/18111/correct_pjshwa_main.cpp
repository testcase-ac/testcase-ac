#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[500][500];
int main() {
  fast_io();

  int n, m, b;
  cin >> n >> m >> b;

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

  int mt = 2e9, mh = -1;
  for (int h = 0; h <= 256; h++) {
    int nb = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) nb += max(0, h - a[i][j]);

    int ct = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      int d = abs(h - a[i][j]);
      if (h > a[i][j]) ct += d;
      else {
        nb -= d;
        ct += 2 * d;
      }
    }

    if (nb <= b && mt >= ct) {
      mt = ct;
      mh = h;
    }
  }
  
  cout << mt << ' ' << mh;
}
