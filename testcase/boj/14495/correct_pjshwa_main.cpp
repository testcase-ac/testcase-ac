#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 116;
ll d[MAX + 1];

void solve() {
  int n; cin >> n;
  
  d[1] = d[2] = d[3] = 1;
  for (int i = 4; i <= n; i++) {
    d[i] = d[i - 1] + d[i - 3];
  }
  cout << d[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
