#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int d[MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) cin >> d[i];

  int r = -1;
  for (int i = 1; i <= n; i++) {
    if (d[i]) continue;
    if (r != -1) return cout << "-1\n", void();
    r = i;
  }
  if (r == -1) return cout << "-1\n", void();

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
