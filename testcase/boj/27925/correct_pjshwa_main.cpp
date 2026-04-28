#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
int A[MAX + 1], d[MAX + 1][10][10][10];
int N;

int r(int i, int a, int b, int c) {
  if (d[i][a][b][c] != -1) return d[i][a][b][c];
  if (i == N) return d[i][a][b][c] = 0;

  int ret = INF, tar = A[i + 1];

  int adif = min(abs(a - tar), 10 - abs(a - tar));
  ret = min(ret, r(i + 1, tar, b, c) + adif);

  int bdif = min(abs(b - tar), 10 - abs(b - tar));
  ret = min(ret, r(i + 1, a, tar, c) + bdif);

  int cdif = min(abs(c - tar), 10 - abs(c - tar));
  ret = min(ret, r(i + 1, a, b, tar) + cdif);

  return d[i][a][b][c] = ret;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
