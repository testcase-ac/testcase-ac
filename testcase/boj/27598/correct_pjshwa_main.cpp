#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int a[MAX + 1], b[MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i <= n; ++i) cin >> b[i];

  int j = n;
  for (int i = n; i >= 1; --i) {
    if (j > 0 && a[i] == b[j]) --j;
  }
  cout << j << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
