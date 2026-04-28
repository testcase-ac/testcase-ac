#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  map<int, int> T;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    T[x]++;
  }

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    ans += (N - T[x]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
