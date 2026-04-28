#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  ll ans = 1 % K;
  for (int i = 2; i <= N; i++) {
    int z = to_string(i).size();
    for (int j = 0; j < z; j++) ans = (ans * 10) % K;
    ans = (ans + i) % K;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
