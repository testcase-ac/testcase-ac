#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll A[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    if (A[i] > A[i - 1]) continue;

    ++ans; A[i] += K;
    if (A[i] <= A[i - 1]) return cout << "-1\n", void();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
