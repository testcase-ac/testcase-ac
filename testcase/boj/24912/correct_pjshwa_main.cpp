#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    if (a[i]) continue;
    for (int c : {1, 2, 3}) {
      if (i && a[i - 1] == c) continue;
      if (i + 1 < n && a[i + 1] == c) continue;
      a[i] = c;
      break;
    }
  }

  for (int i = 0; i < n - 1; i++) {
    if (a[i] == a[i + 1]) return cout << "-1\n", void();
  }

  for (int i = 0; i < n; i++) cout << a[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
