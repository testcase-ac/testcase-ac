#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  ll u = 0, lb = 0, ub = 1e18;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;

    u = x - u;
    if (i & 1) lb = max(lb, -u);
    else ub = min(ub, u);
  }

  cout << max(0LL, ub - lb + 1) << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
