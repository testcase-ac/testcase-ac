#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], dpL[MAXN], dpR[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  dpL[0] = dpR[N - 1] = 1;
  for (int i = 1; i < N; ++i) dpL[i] = min(dpL[i - 1] + 1, A[i]);
  for (int i = N - 2; i >= 0; --i) dpR[i] = min(dpR[i + 1] + 1, A[i]);

  ll ans = 0;
  for (int i = 0; i < N; ++i) ans += min(dpL[i], dpR[i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
