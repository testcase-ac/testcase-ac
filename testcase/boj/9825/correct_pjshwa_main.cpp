#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX][5], d[MAX][5];
int N;

int r(int i, int v) {
  if (d[i][v] != -1) return d[i][v];
  if (i == N - 1) return d[i][v] = A[i][v];

  int ret = 0;
  for (int p = 0; p < 5; p++) {
    ret += A[i][p] * r(i + 1, (v - p + 5) % 5);
  }
  return d[i][v] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    int s, e; cin >> s >> e;
    for (int j = s; j <= e; j++) A[i][j % 5]++;
  }

  memset(d, -1, sizeof(d));
  int ans = 0;
  for (int v = 0; v < 5; v++) {
    int val = (v * v * v * v + 2 * v * v) % 5 + 1;
    ans += r(0, v) * val;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
