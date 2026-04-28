#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 13;
int w[MAX];
int d[10][1 << MAX][21];
int n, m, c;

int rec(int idx, int vstate, int cwgt) {
  if (idx == m) return __builtin_popcount(vstate);
  if (d[idx][vstate][cwgt] != -1) return d[idx][vstate][cwgt];

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (vstate & (1 << i)) continue;
    if (cwgt + w[i] > c) continue;
    ans = max(ans, rec(idx, vstate | (1 << i), cwgt + w[i]));
  }
  ans = max(ans, rec(idx + 1, vstate, 0));

  return d[idx][vstate][cwgt] = ans;
}

int main() {
  fast_io();

  cin >> n >> m >> c;
  for (int i = 0; i < n; ++i) cin >> w[i];
  memset(d, -1, sizeof(d));

  cout << rec(0, 0, 0) << '\n';
}
