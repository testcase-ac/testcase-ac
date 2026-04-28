#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000, INF = 1e9 + 7;
int a[MAX], oa[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 2 * n; i++) cin >> a[i], oa[i] = a[i];

  bool ident = true;
  for (int j = 0; j < 2 * n; j++) ident &= a[j] == j + 1;
  if (ident) return cout << "0\n", void();

  bool flag = true;
  int ans = INF;

  for (int it = 1; it <= 2 * n; it++) {
    if (flag) {
      for (int j = 0; j < n; j++) swap(a[2 * j], a[2 * j + 1]);
    }
    else {
      for (int j = 0; j < n; j++) swap(a[j], a[j + n]);
    }
    flag = !flag;

    bool ident = true;
    for (int j = 0; j < 2 * n; j++) ident &= a[j] == j + 1;

    if (ident) {
      ans = min(ans, it);
      break;
    }
  }

  flag = false;
  for (int i = 0; i < 2 * n; i++) a[i] = oa[i];

  for (int it = 1; it <= 2 * n; it++) {
    if (flag) {
      for (int j = 0; j < n; j++) swap(a[2 * j], a[2 * j + 1]);
    }
    else {
      for (int j = 0; j < n; j++) swap(a[j], a[j + n]);
    }
    flag = !flag;

    bool ident = true;
    for (int j = 0; j < 2 * n; j++) ident &= a[j] == j + 1;

    if (ident) {
      ans = min(ans, it);
      break;
    }
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
