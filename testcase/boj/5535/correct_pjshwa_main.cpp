#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, INF = 1e9 + 7;
int t[MAX], d[MAX + 1][MAX + 1];
tii c[MAX];

int main() {
  fast_io();

  int n, w;
  cin >> n >> w;
  for (int i = 0; i < n; i++) cin >> t[i];
  for (int i = 0; i < w; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    c[i] = {x, y, z};
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < w; j++) d[i][j] = -INF;
  for (int j = 0; j < w; j++) {
    auto [x, y, z] = c[j];
    if (x <= t[0] && t[0] <= y) d[0][j] = 0;
  }
  for (int i = 1; i < n; i++) for (int j = 0; j < w; j++) for (int p = 0; p < w; p++) {
    auto [x, y, z] = c[j];
    auto [px, py, pz] = c[p];
    if (x <= t[i] && t[i] <= y) d[i][j] = max(d[i][j], d[i - 1][p] + abs(z - pz));
  }
  cout << *max_element(d[n - 1], d[n - 1] + w) << '\n';
}
