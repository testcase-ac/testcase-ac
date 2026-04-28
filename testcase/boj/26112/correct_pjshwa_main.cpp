#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
string A[MAX], P1[MAX], P2[MAX];
int d[MAX + 1][MAX + 1][MAX + 1];
int n, p, q;

int r(int i, int j, int l) {
  if (d[i][j][l] != -1) return d[i][j][l];
  if (l == n) return 0;

  int ret = r(i, j, l + 1);
  if (i < p) {
    ret = max(ret, r(i + 1, j, l));
    if (A[l] == P1[i]) ret = max(ret, r(i + 1, j, l + 1) + 1);
  }
  if (j < q) {
    ret = max(ret, r(i, j + 1, l));
    if (A[l] == P2[j]) ret = max(ret, r(i, j + 1, l + 1) + 1);
  }
  return d[i][j][l] = ret;
}

void solve() {
  cin >> n >> p >> q;
  for (int i = 0; i < n; i++) cin >> A[i];
  for (int i = 0; i < p; i++) cin >> P1[i];
  for (int i = 0; i < q; i++) cin >> P2[i];

  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
