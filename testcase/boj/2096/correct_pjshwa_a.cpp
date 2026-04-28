#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int dpm[2][3], dpx[2][3];
int main() {
  fast_io();

  int n, s;
  cin >> n;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> s;
      dpm[i % 2][j] = dpx[i % 2][j] = s;
    }
    dpx[i % 2][0] += max(dpx[(i + 1) % 2][0], dpx[(i + 1) % 2][1]);
    dpx[i % 2][1] += max(max(dpx[(i + 1) % 2][0], dpx[(i + 1) % 2][1]), dpx[(i + 1) % 2][2]);
    dpx[i % 2][2] += max(dpx[(i + 1) % 2][1], dpx[(i + 1) % 2][2]);

    dpm[i % 2][0] += min(dpm[(i + 1) % 2][0], dpm[(i + 1) % 2][1]);
    dpm[i % 2][1] += min(min(dpm[(i + 1) % 2][0], dpm[(i + 1) % 2][1]), dpm[(i + 1) % 2][2]);
    dpm[i % 2][2] += min(dpm[(i + 1) % 2][1], dpm[(i + 1) % 2][2]);
  }
  int mx = max(max(dpx[(n - 1) % 2][0], dpx[(n - 1) % 2][1]), dpx[(n - 1) % 2][2]);
  int mn = min(min(dpm[(n - 1) % 2][0], dpm[(n - 1) % 2][1]), dpm[(n - 1) % 2][2]);
  cout << mx << ' ' << mn << '\n';
}
