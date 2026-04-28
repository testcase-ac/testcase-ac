#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int p = 0, q = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x; x %= 3;
    if (x == 0) q++;
    if (x == 1) p++;
    if (x == 2) q--, p--;
  }
  cout << p << ' ' << q << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
