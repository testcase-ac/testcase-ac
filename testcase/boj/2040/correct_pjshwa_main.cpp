#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000, INF = 0x3f3f3f3f;
int A[MAX + 1], d[MAX + 1][2];

int r(int i, int p) {
  if (d[i][p] != INF) return d[i][p];
  if (i == 0) return d[i][p] = 0;

  int ret = p ? -INF : INF, acc = 0;
  for (int j = i; j >= 1; j--) {
    acc += A[j];
    if (p) ret = max(ret, -acc + r(j - 1, 0));
    else ret = min(ret, acc + r(j - 1, 1));
  }
  return d[i][p] = ret;
}

void solve() {
  int n; cin >> n;
  for (int t = 0; t < 3; t++) {
    for (int i = 1; i <= n; i++) cin >> A[i];

    memset(d, 0x3f, sizeof(d));
    int res = r(n, 0);
    if (res < 0) cout << "A\n";
    else if (res > 0) cout << "B\n";
    else cout << "D\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
