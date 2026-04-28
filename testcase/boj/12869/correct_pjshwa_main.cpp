#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int d[61][61][61];

int r(int u, int v, int w) {
  if (u == 0 && v == 0 && w == 0) return 0;
  if (d[u][v][w] != -1) return d[u][v][w];

  int ans = INF;
  int p[3] = {1, 3, 9};

  do {
    ans = min(ans, r(max(0, u - p[0]), max(0, v - p[1]), max(0, w - p[2])) + 1);
  } while (next_permutation(p, p + 3));
  return d[u][v][w] = ans;
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  int n, u[3] = {0};
  cin >> n;
  for (int i = 0; i < n; i++) cin >> u[i];

  cout << r(u[0], u[1], u[2]);
}
