#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> a[i][j];

  if (n & 1) {
    for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < m - 1; j++) cout << 'R';
      cout << 'D';
      for (int j = 0; j < m - 1; j++) cout << 'L';
      cout << 'D';
    }
    for (int j = 0; j < m - 1; j++) cout << 'R';
  }
  else if (m & 1) {
    for (int j = 0; j < m / 2; j++) {
      for (int i = 0; i < n - 1; i++) cout << 'D';
      cout << 'R';
      for (int i = 0; i < n - 1; i++) cout << 'U';
      cout << 'R';
    }
    for (int i = 0; i < n - 1; i++) cout << 'D';
  }
  else {
    int mi = 0, mj = 1;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
      if ((i + j) % 2 == 0) continue;
      if (a[i][j] < a[mi][mj]) mi = i, mj = j;
    }

    int ci = 0, cj = 0;
    while (mi >= ci + 2) {
      for (int j = 0; j < m - 1; j++) cout << 'R';
      cout << 'D';
      for (int j = 0; j < m - 1; j++) cout << 'L';
      cout << 'D';

      ci += 2;
    }

    if (mi == ci) {
      while (mj >= cj + 2) {
        cout << "DRUR";
        cj += 2;
      }
      cout << "DR";
      cj++;
      while (cj < m - 1) {
        cout << "RURD";
        cj += 2;
      }
    }
    else {
      while (mj >= cj + 2) {
        cout << "DRUR";
        cj += 2;
      }
      cout << "RD";
      cj++;
      while (cj < m - 1) {
        cout << "RURD";
        cj += 2;
      }
    }
    ci++;
    if (ci < n - 1) {
      cout << 'D';
      ci++;

      while (ci < n) {
        for (int j = 0; j < m - 1; j++) cout << 'L';
        cout << 'D';
        for (int j = 0; j < m - 1; j++) cout << 'R';
        if (ci < n - 2) cout << 'D';

        ci += 2;
      }
    }

  }

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
