#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX], n;
int d[2][2][MAX];

int r(int i, int r1, int r2) {
  if (d[r1][r2][i] != -1) return d[r1][r2][i];

  bool ret = false;
  if (i == n - 2) ret = a[i + 1] == (r1 != r2);
  else {
    for (int nr1 : {0, 1}) for (int nr2 : {0, 1}) {
      int score = abs((r1 + nr1) - (r2 + nr2));
      if (a[i + 1] == score) ret |= r(i + 1, nr1, nr2);
    }
  }
  return d[r1][r2][i] = ret;
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  memset(d, -1, sizeof(d));

  bool ans = false;
  for (int r1 : {0, 1}) for (int r2 : {0, 1}) {
    if (a[0] == (r1 != r2)) ans |= r(0, r1, r2);
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
