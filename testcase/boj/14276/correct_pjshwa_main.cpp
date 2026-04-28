#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30, MOD = 1e9 + 7;
int d[MAX + 1][MAX + 1][9][1 << 9];
int N, M, K;

int r(int n, int m, int k, int state) {
  if (n > N || m == 0) return m == 0 && state == 0;
  if (k > K || n + k >= N) {
    if (state & 1) return 0;
    else return r(n + 1, m, 1, state >> 1);
  }

  if (d[n][m][k][state] != -1) return d[n][m][k][state];
  int res = r(n, m, k + 1, state);
  res = (res + r(n, m - 1, k, state ^ 1 ^ (1 << k))) % MOD;
  return d[n][m][k][state] = res;
}

void solve() {
  cin >> N >> M >> K;
  memset(d, -1, sizeof(d));
  cout << r(0, M, 1, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
