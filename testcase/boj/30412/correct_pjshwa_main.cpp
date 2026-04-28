#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e6, INF = 1e18;
ll A[MAX];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll ans = INF;
  ans = min(ans, max(0LL, A[0] + K - A[1]));
  ans = min(ans, max(0LL, A[1] + K - A[0]));
  ans = min(ans, max(0LL, A[N - 1] + K - A[N - 2]));
  ans = min(ans, max(0LL, A[N - 2] + K - A[N - 1]));

  for (int i = 1; i < N - 1; ++i) {
    ans = min(ans, max({0LL, A[i - 1] + K - A[i], A[i + 1] + K - A[i]}));
    ans = min(ans, max(0LL, A[i] + K - A[i - 1]) + max(0LL, A[i] + K - A[i + 1]));

    {
      ll a = A[i - 1], b = A[i], c = A[i + 1], cur = 0;
      if (b < a + K) b = a + K, cur += b - A[i];
      if (c < b + K) c = b + K, cur += c - A[i + 1];
      ans = min(ans, cur);
    }
    {
      ll a = A[i + 1], b = A[i], c = A[i - 1], cur = 0;
      if (b < a + K) b = a + K, cur += b - A[i];
      if (c < b + K) c = b + K, cur += c - A[i - 1];
      ans = min(ans, cur);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
