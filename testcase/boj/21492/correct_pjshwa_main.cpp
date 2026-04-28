#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll P[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; ++i) cin >> P[i], P[i] += P[i - 1];

  multiset<ll> U;
  for (int i = K; i + K <= N; ++i) U.insert(P[i + K] - P[i]);
  ll ans = *U.rbegin();

  for (int i = K + 1; i <= N; ++i) {
    if (i <= N - K + 1) {
      U.erase(U.find(P[i + K - 1] - P[i - 1]));
    }
    if (i >= 2 * K) {
      U.insert(P[i - K] - P[i - 2 * K]);
    }
    ans = min(ans, *U.rbegin());
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
