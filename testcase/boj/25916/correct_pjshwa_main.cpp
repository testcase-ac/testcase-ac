#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
ll A[MAX + 1];

void solve() {
  ll N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> A[i];

  ll run = 0, l = 0, ans = 0;
  for (int r = 1; r <= N; r++) {
    run += A[r];
    while (run > M) run -= A[++l];

    ans = max(ans, run);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
