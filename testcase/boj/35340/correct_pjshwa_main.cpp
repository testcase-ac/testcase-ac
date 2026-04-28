#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1e5, INF = 1e18;
ll A[MAXN];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 1; i < N; ++i) A[i] = min(A[i], 2 * A[i - 1]);

  while (Q--) {
    ll x, acc = 0, ans = INF; cin >> x;
    for (int b = min(30, N - 1); b >= 0; --b) {
      ll cur = (1LL << b), t = x / cur;
      x -= t * cur; acc += t * A[b];
      ans = min(ans, acc + A[b]);
    }
    cout << min(ans, acc) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
