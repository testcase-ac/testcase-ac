#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int a[MAX];
bool d[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) cin >> a[i];

  d[0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (d[j] && (i - j) * (1 + abs(a[i] - a[j])) <= k) d[i] = 1;
    }
  }
  cout << (d[n - 1] ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
