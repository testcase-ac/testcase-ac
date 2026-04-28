#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  cout << "1\n";
  cout << "(0,0)\n";
  for (int i = 0; i < n; i++) {
    if (i & 1) for (int j = m - 1; j >= 1; j--) cout << "(" << i << "," << j << ")\n";
    else for (int j = 1; j < m; j++) cout << "(" << i << "," << j << ")\n";
  }
  for (int i = n - 1; i >= 1; i--) cout << "(" << i << "," << "0)\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
