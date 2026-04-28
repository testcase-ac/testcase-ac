#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll A[MAX + 1], d[MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i], A[i] += A[i - 1];

  for (int i = 0; i <= N; i++) {
    if (i) d[i] = max(d[i], d[i - 1]);

    int j = lower_bound(A, A + N + 1, A[i] + K) - A;
    if (j <= N && A[j] - A[i] >= K) d[j] = max(d[j], d[i] + A[j] - A[i] - K);
  }
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
