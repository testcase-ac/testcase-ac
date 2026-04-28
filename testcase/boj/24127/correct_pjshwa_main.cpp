#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 2400;
ll A[MAXM + 1];

void solve() {
  ll m, p, q; cin >> m >> p >> q;

  int mul = 2 * m + 1;
  for (int i = 1; i <= m; i++) {
    cin >> A[i];
    A[i] = (A[i] & 1);
  }
  for (int i = m + 1; i <= mul * m; i++) {
    A[i] = A[i - m] ^ A[i - 1];
  }

  for (int i = 1; i <= mul * m; ++i) {
    cout << A[i];
    if (i % m == 0) cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
