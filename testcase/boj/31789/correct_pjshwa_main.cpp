#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, X, S; cin >> N >> X >> S;

  int maxp = 0;
  for (int i = 0; i < N; ++i) {
    int c, p; cin >> c >> p;
    if (c <= X) maxp = max(maxp, p);
  }

  if (maxp > S) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
