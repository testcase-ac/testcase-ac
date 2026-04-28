#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10;
ll A[MAXN];

void solve() {
  ll N, T; cin >> N >> T;
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll ans = 0;
  for (int s = 1; s < (1 << N); ++s) {
    ll prd = 1;
    for (int i = 0; i < N; ++i) {
      if (s & (1 << i)) prd *= A[i];
    }
    ll sum = T / prd;
    if (__builtin_popcount(s) % 2 == 0) sum *= -1;
    ans += sum;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
