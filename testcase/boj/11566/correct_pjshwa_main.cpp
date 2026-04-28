#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, INF = 1e9 + 7;
int a[MAX], b[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> m;
  for (int i = 0; i < m; i++) cin >> b[i];

  int minl = -1, maxl = -1;
  for (int gap = 1; gap <= 1000; gap++) {
    for (int si = 0; si < m; si++) {
      if (si + (n - 1) * gap >= m) break;

      bool able = true;
      for (int j = 0; j < n; j++) {
        if (a[j] != b[si + j * gap]) {
          able = false;
          break;
        }
      }
      if (able) {
        if (minl == -1) minl = gap - 1;
        maxl = gap - 1;
      }
    }
  }

  if (minl == -1) cout << "-1\n";
  else cout << minl << " " << maxl << '\n';
}
