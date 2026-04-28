#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2500;
int A[MAX + 10], d[MAX + 1][MAX + 1];
int N;

int r(int i, int p, int val) {
  if (i == N + 1) return 0;
  if (d[i][p] != -1) return d[i][p];
  if (i == N) return d[i][p] = val != 0;

  int res = r(i + 1, i + 1, A[i + 1]) + 1;
  if (val == A[i + 1]) res = min(res, r(i + 2, i + 2, A[i + 2]) + 1);
  else if (val < A[i + 1]) res = min(res, r(i + 1, p, A[i + 1] - val) + 1);

  return d[i][p] = res;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  memset(d, -1, sizeof(d));
  cout << r(1, 1, A[1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
