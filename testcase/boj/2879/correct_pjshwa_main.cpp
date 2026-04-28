#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN];

void solve() {
  int N, x; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> x, A[i] -= x;

  int ans = 0, lsgn = 0, lval = -1;
  for (int i = 0; i < N; ++i) {
    int sgn = A[i] >= 0 ? 1 : -1, val = abs(A[i]);
    if (lsgn * sgn < 1) ans += val;
    else if (lval < val) ans += val - lval;
    lsgn = sgn, lval = val;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
