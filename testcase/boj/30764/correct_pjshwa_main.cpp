#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int O[MAXV + 1];

void solve() {
  int n, a, b, c; cin >> n >> a >> b >> c;
  for (int i = 0; i < n; ++i) {
    int l, r; cin >> l >> r;
    for (int j = l; j <= r; ++j) O[j] = 1;
  }

  int cnt = 0;
  for (int i = 1; i <= b; ++i) cnt += O[i];
  if (cnt > c) return cout << "No\n", void();

  for (int i = b + 1; i <= MAXV; ++i) {
    cnt += O[i] - O[i - b];
    if (cnt > c) return cout << "No\n", void();
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
