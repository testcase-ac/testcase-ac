#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll A[MAXN + 1];

void solve() {
  int X, Q; cin >> X >> Q;

  A[1] = X + 1;
  for (int i = 2; i <= MAXN; ++i) {
    if (A[i - 1] % i == 0) A[i] = A[i - 1] + i;
    else A[i] = A[i - 1] + (i - A[i - 1] % i);
  }

  ll l = A[MAXN] / MAXN;
  while (Q--) {
    int v; cin >> v;
    if (v <= MAXN) cout << A[v] << '\n';
    else cout << (ll)v * l << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
