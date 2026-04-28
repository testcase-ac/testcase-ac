#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i], A[i] *= 100;
  for (int i = 0; i < N; ++i) A[i] += K * i;

  int ans = 0, run_max = A[0];
  for (int i = 1; i < N; ++i) {
    ans = max(ans, run_max - A[i] - K);
    run_max = max(run_max, A[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
