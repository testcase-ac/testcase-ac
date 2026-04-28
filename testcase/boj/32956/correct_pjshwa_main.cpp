#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll A[MAXN], B[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];

  int l = 1, r = 1e9 + 1;
  while (l < r) {
    ll m = (l + r) / 2, cnt = 0;
    for (int i = 0; i < N; ++i) {
      if (B[i] < m) continue;
      ll x = (B[i] - m) / A[i] + 1;
      cnt += x;
    }
    if (cnt >= K) l = m + 1;
    else r = m;
  }

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    if (B[i] < l) continue;
    ll x = (B[i] - l) / A[i] + 1;
    K -= x;
    ans += B[i] * x - A[i] * x * (x - 1) / 2;
  }
  --l;
  for (int i = 0; i < N && K > 0; ++i) {
    if (B[i] < l || (B[i] - l) % A[i] != 0) continue;
    ans += l; --K;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
