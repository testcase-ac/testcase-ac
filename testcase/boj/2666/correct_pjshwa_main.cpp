#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m, os[20];

int r(int idx, int o1, int o2) {
  if (idx == m - 1) return 0;
  int t = os[idx + 1];
  return min(abs(t - o1) + r(idx + 1, t, o2), abs(t - o2) + r(idx + 1, o1, t));
}

int main() {
  fast_io();

  int o1, o2;
  cin >> n >> o1 >> o2 >> m;

  for (int i = 0; i < m; i++) cin >> os[i];
  cout << r(-1, o1, o2);
}
