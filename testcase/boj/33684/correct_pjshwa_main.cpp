#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  if (A[N - 1] > K) return cout << "0\n", void();
  if (A[0] <= 0) return cout << "-1\n", void();

  ll ans = 1;
  for (int i = 1; i < N; ++i) ans += (K - A[i]) / A[0];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
