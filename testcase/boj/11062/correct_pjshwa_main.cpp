#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int A[MAX], d[MAX + 1][MAX + 1];

int rec(int l, int r) {
  if (d[l][r] != -1) return d[l][r];
  if (l == r) return d[l][r] = 0;
  if (l + 1 == r) return d[l][r] = A[l];

  int ret = 0;
  ret = max(ret, min(rec(l + 1, r - 1), rec(l + 2, r)) + A[l]);
  ret = max(ret, min(rec(l + 1, r - 1), rec(l, r - 2)) + A[r - 1]);

  return d[l][r] = ret;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  cout << rec(0, N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
