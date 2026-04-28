#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e6;
ll R[MAX], C[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> R[i] >> C[i];

  ll ans = 0;
  for (int i = N - 2; i >= 0; i--) {
    ans += R[i] * C[i] * C[N - 1];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
