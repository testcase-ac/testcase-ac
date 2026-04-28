#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 10000, MAXT = 2e5;

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve_small(int N, int K, vector<int>& C) {
  if (N == 0) return cout << "0\n", void();

  vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(N + 1, vector<ll>(MAXV + 1, 0)));
  dp[0][0][0] = 1;

  for (int i = 1; i <= N; ++i) {
    for (int cnt = 0; cnt <= i; ++cnt) for (int k = 0; k <= MAXV; ++k) {
      dp[i][cnt][k] = dp[i - 1][cnt][k];
    }

    int p = C[i - 1] - C[0];
    for (int cnt = 1; cnt <= i; ++cnt) for (int k = p; k <= MAXV; ++k) {
      dp[i][cnt][k] += dp[i - 1][cnt - 1][k - p];
    }
  }

  ll ans = 0;
  for (int cnt = 0; cnt <= N; ++cnt) for (int k = 0; k <= MAXV; ++k) {
    int val = cnt * C[0] + k;
    if (val == K) ans += dp[N][cnt][k];
  }
  cout << ans << '\n';
}

void solve_large(int N, int K, vector<int>& C) {
  vector<ll> dp(MAXT + 1, 0); dp[0] = 1;
  for (int c : C) {
    for (int j = MAXV; j >= c; --j) dp[j] += dp[j - c];
  }
  if (K > MAXT) cout << "0\n";
  else cout << dp[K] << '\n';
}

void solve() {
  int A, B, K; cin >> A >> B >> K;

  vector<int> C;
  for (int p = A; p <= B; ++p) {
    if (is_prime(p)) C.push_back(p);
  }
  int N = C.size();

  int sum = 0;
  if (N <= 50) {
    for (int c : C) sum += c - C[0];
    assert(sum <= MAXV);
    solve_small(N, K, C);
  } else {
    for (int c : C) sum += c;
    assert(sum <= MAXT);
    solve_large(N, K, C);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
