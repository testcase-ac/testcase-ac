#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; cin >> N >> M >> K;
  if (N > 1 && M > 1) return cout << "-1\n", void();
  if (K == 0 && N * M > 2) return cout << "-1\n", void();

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    ll val = (ll)K * (i + j) + 18974;
    cout << val << " \n"[j == M - 1];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
