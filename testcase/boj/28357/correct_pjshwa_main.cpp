#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
ll A[MAXN];

void solve() {
  ll N, K, l = 0, r = 0; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i], r = max(r, A[i]);

  while (l < r) {
    ll m = (l + r) / 2, cnt = 0;
    for (int i = 0; i < N; ++i) cnt += max(0LL, A[i] - m);
    if (cnt > K) l = m + 1;
    else r = m;
  }
  cout << l << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
