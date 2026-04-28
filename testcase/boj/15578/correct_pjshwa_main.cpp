#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
ll A[MAX];

void solve() {
  ll N, K, M; cin >> N >> K >> M;

  ll rep = M / (2 * N * K - 2 * K);
  ll pre = rep * 2 * K;
  M -= rep * (2 * N * K - 2 * K);
  A[0] = A[N - 1] = -rep * K;

  for (int i = 0; i < N; ++i) {
    ll add = min(M, K);
    A[i] += add;
    M -= add;
  }
  for (int i = N - 2; i >= 1; --i) {
    ll add = min(M, K);
    A[i] += add;
    M -= add;
  }

  for (int i = 0; i < N; ++i) cout << A[i] + pre << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
