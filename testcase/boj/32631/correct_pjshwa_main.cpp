#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 5000, INF = 1e18;
ll A[MAXN + 1], B[MAXN + 1], Ak[MAXN + 1], Bk[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i]; A[i] += A[i - 1];
    Ak[i] = INF;
  }
  for (int i = 1; i <= N; ++i) {
    cin >> B[i]; B[i] += B[i - 1];
    Bk[i] = INF;
  }

  for (int k = 1; k <= N; ++k) {
    for (int i = 1; i + k - 1 <= N; ++i) {
      Ak[k] = min(Ak[k], A[i + k - 1] - A[i - 1]);
      Bk[k] = min(Bk[k], B[i + k - 1] - B[i - 1]);
    }
  }

  ll ans = INF;
  for (int k1 = 0; k1 <= N; ++k1) for (int k2 = 0; k2 <= N; ++k2) {
    int rem = 2 * N - k1 - k2;
    if (rem <= K) ans = min(ans, max(Ak[k1], Bk[k2]));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
